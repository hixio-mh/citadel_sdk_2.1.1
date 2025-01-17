/*******************************************************************
 *
 * Copyright 2006
 * Broadcom Corporation
 * 16215 Alton Parkway
 * PO Box 57013
 * Irvine CA 92619-7013
 *
 * Broadcom provides the current code only to licensees who
 * may have the non-exclusive right to use or modify this
 * code according to the license.
 * This program may be not sold, resold or disseminated in
 * any form without the explicit consent from Broadcom Corp
 *
 *******************************************************************/
/*!
******************************************************************
* \file
*   q_modexp.c
*
* \brief
*   This file contains modulo exponentiation routines. There are 
* several flavors of routines using different optimization method.
* For Montgomery's method, q_modexp_mont must be used. Otherwise,
* Barrett' method is the default used in q_modexp.
*
* \author
*   Charles Qi (x2-8439)
*
* \date
*   Originated: 8/16/2006\n
*   Updated: 10/24/2007
*
* \version
*   0.2
*
******************************************************************
*/

#include <stdlib.h>
#include <stdio.h>
#include "q_lip.h"
#include "q_lip_aux.h"

#ifdef QLIP_DEBUG
#include "q_lip_utils.h"
#endif

#ifdef QLIP_USE_PKE_HW
#include "q_pke_hw.h"
#endif

#ifdef QLIP_USE_PKA_HW
#include "q_pka_hw.h"
#endif

#ifdef QLIP_USE_GMP
#include "gmp.h"
#endif

/**********************************************************************
 * q_modexp ()
 * z = a ^ e mod n
 *
 * Description: Modulo exponentiation.
 * Assumptions:
 *  1. all numbers are bignum
 *  2. no optimization based on bit length
 *  3. size (e) <= size (n) = size (a)
 *
 * When SPA/DPA counter measure is compiled in and enabled, this function
 * is retrofited to support the counter measure of split-exponent with 
 * random masking. The actual computation is:
 *   z = ((a^(e-re) mod n) * (a^re mod n)) mod n 
 * where re is a random number obtained from the get_random function.
 *
 * for exponents less than 32-bit in size, such as e=3 or e=65537 used in
 * RSA encryption of signature verification, a performance optimized sequence
 * is used in lieu of the full sequence.
 *
 **********************************************************************/

q_status_t q_modexp (q_lip_ctx_t *ctx,
                     q_lint_t *z,
                     q_lint_t *a,
                     q_lint_t *e,
                     q_lint_t *n)
{
  q_status_t status = Q_SUCCESS;

#ifdef QLIP_USE_PKA_HW
  int i;
  q_mont_t mont;
  volatile uint32_t pka_status;
  uint32_t LIR_p, LIR_c;
  opcode_t sequence[14];
  int msb_e;
#endif

#ifdef QLIP_USE_COUNTER_SPADPA
  q_lint_t re;
#endif

#ifdef QLIP_DEBUG
  printf ("Enter function %s ()\n", __FUNCTION__);
#endif /* QLIP_DEBUG */

#ifdef QLIP_USE_PKA_HW
  /* initialize hardware first */
  q_pka_hw_rst();

if((e->size <= 1) && (n->size <=64)) {
  /* sending command sequence */
  LIR_p = q_pka_sel_LIR(n->size);
  LIR_c = q_pka_sel_LIR(n->size*2);

  /* sending command sequence */
  /* load exponent e*/
  /* x[0] = n (modulus) */
  sequence[0].op1 = PACK_OP1(0, PKA_OP_MTLIRI, PKA_LIR(LIR_p, 2), n->size);
  sequence[0].ptr = n->limb;

  /* load base a */
  /* x[1] = a (base) */
  sequence[1].op1 = PACK_OP1(0, PKA_OP_MTLIRI, PKA_LIR(LIR_p, 1), a->size);
  sequence[1].ptr = a->limb;
  
  /* x[2] = a (base) */
  sequence[2].op1 = PACK_OP1(0, PKA_OP_MTLIRI, PKA_LIR(LIR_p, 3), a->size);
  sequence[2].ptr = a->limb;
  
  /* send sequnence */
  while(q_pka_hw_rd_status() & PKA_STAT_BUSY) {
  }
  q_pka_hw_write_sequence(3, sequence);

  for(i=0; i<4; i++) {
    sequence[i].ptr = NULL;
  }

  msb_e = q_LeadingOne(e->limb[0]);
  for(i=msb_e-1; i>=0; i--) {
    if(e->limb[0] & (1 << i)) {
      /* SQUARE */
      sequence[0].op1 = PACK_OP1 (0, PKA_OP_LMUL, PKA_LIR (LIR_c, 0), PKA_LIR (LIR_p, 1));
      sequence[0].op2 = PACK_OP2 (PKA_LIR (LIR_p, 1), PKA_NULL);

      /* MOD */
      sequence[1].op1 = PACK_OP1 (0, PKA_OP_MODREM, PKA_LIR (LIR_p, 1), PKA_LIR (LIR_c, 0));
      sequence[1].op2 = PACK_OP2 (PKA_NULL, PKA_LIR (LIR_p, 2));

      /* MULTIPLY */
      sequence[2].op1 = PACK_OP1 (0, PKA_OP_LMUL, PKA_LIR (LIR_c, 0), PKA_LIR (LIR_p, 1));
      sequence[2].op2 = PACK_OP2 (PKA_LIR (LIR_p, 3), PKA_NULL);

      /* MOD */
      sequence[3].op1 = PACK_OP1 (PKA_EOS, PKA_OP_MODREM, PKA_LIR (LIR_p, 1), PKA_LIR (LIR_c, 0));
      sequence[3].op2 = PACK_OP2 (PKA_NULL, PKA_LIR (LIR_p, 2));

      /* send sequnence */
      while(q_pka_hw_rd_status() & PKA_STAT_BUSY) {
      }
      q_pka_hw_write_sequence(4, sequence);
    } else {
      /* SQUARE */
      sequence[0].op1 = PACK_OP1 (0, PKA_OP_LMUL, PKA_LIR (LIR_c, 0), PKA_LIR (LIR_p, 1));
      sequence[0].op2 = PACK_OP2 (PKA_LIR (LIR_p, 1), PKA_NULL);

      /* MOD */
      sequence[1].op1 = PACK_OP1 (PKA_EOS, PKA_OP_MODREM, PKA_LIR (LIR_p, 1), PKA_LIR (LIR_c, 0));
      sequence[1].op2 = PACK_OP2 (PKA_NULL, PKA_LIR (LIR_p, 2));

      /* send sequnence */
      while(q_pka_hw_rd_status() & PKA_STAT_BUSY) {
      }
      q_pka_hw_write_sequence(2, sequence);
    }

    while (! ((pka_status = q_pka_hw_rd_status ()) & PKA_STAT_DONE)) {
      if (pka_status & PKA_STAT_ERROR) {
        ctx->status = Q_ERR_PKA_HW_ERR;
        goto Q_MODEXP_EXIT;
      }
    }
    q_pka_hw_wr_status (pka_status);
  }

  /* read back result */
  sequence[0].op1 = PACK_OP1(PKA_EOS, PKA_OP_MFLIRI, PKA_LIR(LIR_p, 1), n->size);

  /* send sequnence */
  while(q_pka_hw_rd_status() & PKA_STAT_BUSY) {
  }
  q_pka_hw_write_sequence(1, sequence);
} else { 
  status = q_init(ctx, &mont.n,  n->alloc);
  status += q_init(ctx, &mont.np, n->alloc+1);
  status += q_init(ctx, &mont.rr, n->alloc+1);
  if(status != Q_SUCCESS) goto Q_MODEXP_EXIT;

  if((status = q_mont_init(ctx, &mont, n)) != Q_SUCCESS) goto Q_MODEXP_EXIT;
  q_pka_hw_rst();

  LIR_p = q_pka_sel_LIR(n->size);

  for(i=0; i<14; i++) {
    sequence[i].ptr = NULL;
  }

  /* sending command sequence */
  /* load exponent e*/
  /* x[0] = e (exponent) */
  sequence[0].op1 = PACK_OP1(0, PKA_OP_MTLIRI, PKA_LIR(LIR_p, 0), e->size);
  sequence[0].ptr = e->limb;

  /* load modulus n */
  /* x[1] = n.n */
  sequence[1].op1 = PACK_OP1(0, PKA_OP_MTLIRI, PKA_LIR(LIR_p, 1), mont.n.size);
  sequence[1].ptr = mont.n.limb;

  /* load montgomery parameter np */
  /* x[2] = n.np */
  sequence[2].op1 = PACK_OP1(0, PKA_OP_MTLIRI, PKA_LIR(LIR_p, 2), mont.np.size);
  sequence[2].ptr = mont.np.limb;

  /* load montgomery parameter rr */
  /* x[3] = n.rr */
  sequence[3].op1 = PACK_OP1(0, PKA_OP_MTLIRI, PKA_LIR(LIR_p, 3), mont.rr.size);
  sequence[3].ptr = mont.rr.limb;

  /* load base a */
  /* x[4] = a (base) */
  sequence[4].op1 = PACK_OP1(0, PKA_OP_MTLIRI, PKA_LIR(LIR_p, 4), a->size);
  sequence[4].ptr = a->limb;
  
#ifdef QLIP_USE_COUNTER_SPADPA
  if(ctx->ESCAPE != 0) {
    q_init(ctx, &re, e->size);
    if(ctx->q_get_random != NULL) {
      ctx->q_get_random(&ctx->lfsr, e->size, re.limb);
      re.size = e->size;
    }

/*reduce re to a value smaller than e */
    msb_e = q_LeadingOne (e->limb[e->size-1]);
    re.limb[re.size-1] &= (0xffffffff >> (32-msb_e));

    /* load random exponent re*/
    /* x[5] = re (random exponent) */
    sequence[5].op1 = PACK_OP1(0, PKA_OP_MTLIRI, PKA_LIR(LIR_p, 5), re.size);
    sequence[5].ptr = re.limb;
  
    /* convert base a to n-residue domain */
    /* x[4] = x[4] * x[3] mod x[1] */
    sequence[6].op1 = PACK_OP1(0, PKA_OP_MODMUL, PKA_LIR(LIR_p, 4), PKA_LIR(LIR_p, 4));
    sequence[6].op2 = PACK_OP2(PKA_LIR(LIR_p, 3), PKA_LIR(LIR_p, 1));
  
    /* compute exponent delta e = e - re */
    sequence[7].op1 = PACK_OP1(0, PKA_OP_LSUB, PKA_LIR(LIR_p, 0), PKA_LIR(LIR_p, 0));
    sequence[7].op2 = PACK_OP2(PKA_LIR(LIR_p, 5), PKA_NULL);
  
    /* perform montgomery modexp a^(e-re) mod n */
    /* x[3] = x[4] ^ x[0] mod x[1] */
    sequence[8].op1 = PACK_OP1(0, PKA_OP_MODEXP, PKA_LIR(LIR_p, 3), PKA_LIR(LIR_p, 4));
    sequence[8].op2 = PACK_OP2(PKA_LIR(LIR_p, 0), PKA_LIR(LIR_p, 1));
  
    /* perform montgomery modexp a^re mod n */
    /* x[0] = x[4] ^ x[5] mod x[1] */
    sequence[9].op1 = PACK_OP1(0, PKA_OP_MODEXP, PKA_LIR(LIR_p, 0), PKA_LIR(LIR_p, 4));
    sequence[9].op2 = PACK_OP2(PKA_LIR(LIR_p, 5), PKA_LIR(LIR_p, 1));
  
    /* perform montgomery modmul */
    /* x[3] = x[3] * x[0] mod x[1] */
    sequence[10].op1 = PACK_OP1(0, PKA_OP_MODMUL, PKA_LIR(LIR_p, 3), PKA_LIR(LIR_p, 3));
    sequence[10].op2 = PACK_OP2(PKA_LIR(LIR_p, 0), PKA_LIR(LIR_p, 1));
  
    /* set LIR = 1 */
    /* x[4] = 1 */
    sequence[11].op1 = PACK_OP1(0, PKA_OP_SLIR, PKA_LIR(LIR_p, 4), PKA_NULL);
    sequence[11].op2 = PACK_OP2(PKA_NULL, 1);
  
    /* convert result back to regular domain */
    /* x[4] = x[4] * x[3] mod x[1] */
    sequence[12].op1 = PACK_OP1(0, PKA_OP_MODMUL, PKA_LIR(LIR_p, 4), PKA_LIR(LIR_p, 4));
    sequence[12].op2 = PACK_OP2(PKA_LIR(LIR_p, 3), PKA_LIR(LIR_p, 1));
  
    /* read back result */
    sequence[13].op1 = PACK_OP1(PKA_EOS, PKA_OP_MFLIRI, PKA_LIR(LIR_p, 4), n->size);
  
    i=14;
  } else {
#endif
    /* convert base a to n-residue domain */
    /* x[4] = x[4] * x[3] mod x[1] */
    sequence[5].op1 = PACK_OP1(0, PKA_OP_MODMUL, PKA_LIR(LIR_p, 4), PKA_LIR(LIR_p, 4));
    sequence[5].op2 = PACK_OP2(PKA_LIR(LIR_p, 3), PKA_LIR(LIR_p, 1));
  
    /* perform montgomery modexp */
    /* x[3] = x[4] ^ x[0] mod x[1] */
    sequence[6].op1 = PACK_OP1(0, PKA_OP_MODEXP, PKA_LIR(LIR_p, 3), PKA_LIR(LIR_p, 4));
    sequence[6].op2 = PACK_OP2(PKA_LIR(LIR_p, 0), PKA_LIR(LIR_p, 1));
  
    /* set LIR = 1 */
    /* x[4] = 1 */
    sequence[7].op1 = PACK_OP1(0, PKA_OP_SLIR, PKA_LIR(LIR_p, 4), PKA_NULL);
    sequence[7].op2 = PACK_OP2(PKA_NULL, 1);
  
    /* convert result back to regular domain */
    /* x[4] = x[4] * x[3] mod x[1] */
    sequence[8].op1 = PACK_OP1(0, PKA_OP_MODMUL, PKA_LIR(LIR_p, 4), PKA_LIR(LIR_p, 4));
    sequence[8].op2 = PACK_OP2(PKA_LIR(LIR_p, 3), PKA_LIR(LIR_p, 1));
  
    /* read back result */
    sequence[9].op1 = PACK_OP1(PKA_EOS, PKA_OP_MFLIRI, PKA_LIR(LIR_p, 4), n->size);

    i= 10;

#ifdef QLIP_USE_COUNTER_SPADPA
  }
#endif

  /* send sequnence */
  while(q_pka_hw_rd_status() & PKA_STAT_BUSY) {
    if ((ctx->status = ctx->q_yield ()) != Q_SUCCESS) goto Q_MODEXP_EXIT;
  }
  q_pka_hw_write_sequence(i, sequence);

#ifdef QLIP_USE_COUNTER_SPADPA
  if(ctx->ESCAPE != 0) {
    re.size = e->size;
    q_free(ctx, &re);
  }
#endif

  q_free(ctx, &mont.rr);
  q_free(ctx, &mont.np);
  q_free(ctx, &mont.n);
}

  z->size = n->size;

  /* read result back */
  while (!((pka_status = q_pka_hw_rd_status ()) & PKA_STAT_DONE)) {
#ifdef QLIP_USE_COUNTER_SPADPA
    if(ctx->ESCAPE != 0) { //opportunistically shift LFSR
      q_shift_lfsr(&ctx->lfsr, 31);
    }
#endif

    if (pka_status & PKA_STAT_ERROR) {
      ctx->status = Q_ERR_PKA_HW_ERR;
      goto Q_MODEXP_EXIT;
    } else {
      if ((ctx->status = ctx->q_yield ()) != Q_SUCCESS) goto Q_MODEXP_EXIT;
    }
  }
  q_pka_hw_wr_status(pka_status);
  q_pka_hw_read_LIR(z->size, z->limb);

#else /* QLIP_USE_PKA_HW */
#ifdef QLIP_USE_PKE_HW
  q_lint_t ta, te, tn;

  q_SetOne (z);
  if (q_IsZero (e)) {
    return (0);
  }

  status = q_init (ctx, &ta, n->alloc);
  status += q_init (ctx, &te, e->alloc);
  status += q_init (ctx, &tn, n->alloc);

  if (status != Q_SUCCESS) goto Q_MODEXP_EXIT;

  status = q_copy (&ta, a);
  status += q_copy (&te, e);
  status += q_copy (&tn, n);

  if (status != Q_SUCCESS) {
    ctx->status = Q_ERR_DST_OVERFLOW;
    goto Q_MODEXP_EXIT;
  }

  q_modexp_hw (z->limb, n->size*MACHINE_WD, e->size*MACHINE_WD, tn.limb, te.limb, ta.limb);
  z->size = n->size;
  Q_NORMALIZE (z->limb, z->size);
  q_free (ctx, &tn);
  q_free (ctx, &te);
  q_free (ctx, &ta);
#else /* QLIP_USE_PKE_HW */
  int i, j;
  q_size_t es;
  q_limb_ptr_t ep, zp;
  int bitset; /* points to the current machine word */

  q_lint_t r;
  q_limb_ptr_t rp;
  uint32_t rs;

  q_SetOne (z);
  if (q_IsZero (e)) {
    goto Q_MODEXP_EXIT;
  }

  /* bump up the size of z to the size of n */
  z->size = n->size;

  es = e->size;
  ep = e->limb;
  zp = z->limb;

  /* pre-computation for PB method */
#ifdef QLIP_MOD_USE_PB

  rs = (n->size)*2 + 1;

  if (q_init (ctx, &r, rs)) goto Q_MODEXP_EXIT; /* allocate 2n+1 limb */
  r.size = rs;
  rp = r.limb;
  rp[rs-1] = 1L;
  if (q_div (ctx, &r, &r, n)) goto Q_MODEXP_EXIT;
  Q_NORMALIZE (rp, r.size);
#endif /* QLIP_MOD_USE_PB */

  /* the exponential loop */

#ifdef QLIP_MODEXP_RL_BIN
  /* RL binary method */
  /* The RL binary method requires an extra storage if the location of a can't be reused.
     This is not supported by the following code. */
  for (i=0; i < es; i++) {
    for (j=0; j < MACHINE_WD; j++) {
      bitset = ep[i] & (1 << j);
      if (bitset) {
#ifdef QLIP_MOD_USE_PB
        if (q_modmul_pb (ctx, z, &r, z, a, n)) goto Q_MODEXP_EXIT;
#else /* QLIP_MOD_USE_PB */
        if (q_modmul (ctx, z, z, a, n)) goto Q_MODEXP_EXIT;
#endif /* QLIP_MOD_USE_PB */
      }
      if ((i != es-1) || (j != MACHINE_WD-1)) {
#ifdef QLIP_MOD_USE_PB
        if (q_modsqr_pb (ctx, a, &r, a, n)) goto Q_MODEXP_EXIT;
#else /* QLIP_MOD_USE_PB */
        if (q_modsqr (ctx, a, a, n)) goto Q_MODEXP_EXIT;
#endif /* QLIP_MOD_USE_PB */
      }
    }
  }
#endif /* QLIP_MODEXP_RL_BIN */

#ifdef QLIP_MODEXP_LR_BIN
  /* LR binary method */
  for (i=es-1; i >= 0; i--) {
    for (j=MACHINE_WD-1; j >= 0; j--) {
      bitset = ep[i] & (1 << j);
      if (bitset) {
#ifdef QLIP_MOD_USE_PB
        if (q_modmul_pb (ctx, z, &r, z, a, n)) goto Q_MODEXP_EXIT;
#else /* QLIP_MOD_USE_PB */
        if (q_modmul (ctx, z, z, a, n)) goto Q_MODEXP_EXIT;
#endif /* QLIP_MOD_USE_PB */
      }
      if ((i != 0) || (j != 0)) {
#ifdef QLIP_MOD_USE_PB
        if (q_modsqr_pb (ctx, z, &r, z, n)) goto Q_MODEXP_EXIT;
#else /* QLIP_MOD_USE_PB */
        if (q_modsqr (ctx, z, z, n)) goto Q_MODEXP_EXIT;
#endif /* QLIP_MOD_USE_PB */
      }
    }
  }
#endif /* QLIP_MODEXP_LR_BIN */

#ifdef QLIP_MOD_USE_PB
	q_free(ctx, &r);
#endif /* QLIP_MOD_USE_PB */

  Q_NORMALIZE (zp, z->size);

#endif /* QLIP_USE_PKE_HW */
#endif /* QLIP_USE_PKA_HW */

 Q_MODEXP_EXIT:

#ifdef QLIP_DEBUG
  printf ("Exit function %s ()\n", __FUNCTION__);
#endif /* QLIP_DEBUG */

  return (ctx->status);
}

/**********************************************************************
 * q_mont_init ()
 *
 * Description: Montgomery parameter initialization. This function
 * computes the following elements from the modulus n:
 *  np, rr, where
 *  r = 1 << (word_size (n) * 32),
 *  rr = r ^ 2 mod n,
 *  r * r_inv - n * np = 1.
 **********************************************************************/

q_status_t q_mont_init (q_lip_ctx_t *ctx,
                        q_mont_t *mont,
                        q_lint_t *n)
{
  q_status_t status = Q_SUCCESS;
  int i;
  q_limb_ptr_t np;
  q_size_t ns;
  int br;
  q_lint_t c1;
  q_lint_t rr;

#ifdef QLIP_USE_GMP
  mpz_t mn, mnp, mr, mri;
  mpz_t mc1;
#endif

#ifdef QLIP_USE_PKA_HW
  q_lint_t lx;
  opcode_t sequence[6];
  uint32_t LIR_n, LIR_rr;
  volatile uint32_t pka_status;
  int R_idx, Q_idx;
#endif

#ifdef QLIP_DEBUG
  printf ("Enter function %s ()\n", __FUNCTION__);
#endif /* QLIP_DEBUG */

  np = n->limb;
  ns = n->size;
  if ((ctx->status = q_copy (&mont->n, n)) != Q_SUCCESS) goto Q_MONT_INIT_EXIT;

#ifdef QLIP_USE_GMP
  mpz_init (mr);
  mpz_init (mri);
  mpz_init (mn);
  mpz_init (mnp);
  mpz_init (mc1);

  mpz_set_si (mc1, 1);

  /* R = 2^br */
  /* determine the size of R */
#if 1
  /*
    PKA HW requires R be constructed as follows:
    R = 1 << (32*(n->size)),
    where n->size is number of 32-bit words of n.
  */
  br = (n->size) << BITS_FOR_MACHINE_WD;
#endif

#if 0
/*
    The following code constructs R as follows:
    R = 1 << (number of significant bits in n)

		This is a firmware only optimization that can be done.
    However, the result of this optimization would cause
    q_mont_init output to deviate from the PKA implementation.
    In particular, mont_test.c would fail.
	
    Fundamentally, the two approach result in two residue domains.
    The intermediate computation in two domains are different. However,
    if we compute only the final normal result for modexp, the results
    would match when they are converted back from two residue domains.

    ZQI 8/16/2007
*/
  br = q_LeadingOne (n->limb[n->size-1]);
  br += ((n->size-1) << BITS_FOR_MACHINE_WD) + 1;
#endif

  mont->br = br;

  /* N */
  mpz_import (mn, n->size, -1, 4, 0, 0, n->limb);

  /* R */
  mpz_mul_2exp (mr, mc1, br);

  /* Ri = R^-1 mod N */
  mpz_invert (mri, mr, mn);

  /* R.Ri - 1 */
  mpz_mul (mri, mr, mri);
  mpz_sub (mri, mri, mc1);

  /* Np = (R.Ri-1)/N */
  mpz_div (mnp, mri, mn);
  mpz_export (mont->np.limb, &(mont->np.size), -1, 4, 0, 0, mnp);

  /* R^2 */
  mpz_mul_2exp (mr, mc1, br*2);
  mpz_mod (mr, mr, mn);
  mpz_export (mont->rr.limb, &(mont->rr.size), -1, 4, 0, 0, mr);

  if (mont->np.size < mont->n.size) {
    for (i=mont->np.size; i<mont->n.size; i++) {
      mont->np.limb[i] = 0;
    }
    mont->np.size = mont->n.size;
  }

  if (mont->rr.size < mont->n.size) {
    for (i=mont->rr.size; i<mont->n.size; i++) {
      mont->rr.limb[i] = 0;
    }
    mont->rr.size = mont->n.size;
  }

  mpz_clear (mr);
  mpz_clear (mri);
  mpz_clear (mn);
  mpz_clear (mnp);
  mpz_clear (mc1);

#else /* QLIP_USE_GMP */

#ifdef QLIP_USE_PKA_HW
  status  = q_init (ctx, &rr, n->alloc+1);
  status += q_init (ctx, &lx, n->alloc);
  if (status != Q_SUCCESS) goto Q_MONT_INIT_EXIT;

  lx.limb[0] = 1;

  rr.size = 1 + n->size;
  rr.limb[n->size] = 1L;

  mont->br = (n->size) << BITS_FOR_MACHINE_WD;

  LIR_n = q_pka_sel_LIR (n->size);
  LIR_rr = LIR_n + (1<<8);
  if (q_pka_LIR_size (LIR_n) * 2 == q_pka_LIR_size (LIR_rr)) {
    R_idx = 1;
    Q_idx = 2;
  } else {
    R_idx = 2;
    Q_idx = 3;
  }

  /*
    Calculate the following elements:
    R mod N
    R / N
  */

  /* x[0] = N */
  sequence[0].op1 = PACK_OP1 (0, PKA_OP_MTLIRI, PKA_LIR (LIR_n, 0), n->size);
  sequence[0].ptr = n->limb;

  /* y[R_idx] = R */
  sequence[1].op1 = PACK_OP1 (0, PKA_OP_MTLIRI, PKA_LIR (LIR_rr, R_idx), rr.size);
  sequence[1].ptr = rr.limb;

  /* x[1] = y[R_idx] mod x[0] (R mod N) */
  sequence[2].op1 = PACK_OP1 (0, PKA_OP_MODREM, PKA_LIR (LIR_n, 1), PKA_LIR (LIR_rr, R_idx));
  sequence[2].op2 = PACK_OP2 (PKA_NULL, PKA_LIR (LIR_n, 0));
  sequence[2].ptr = NULL;

  /* y[Q_idx] = y[R_idx] / x[0] (R / N) */
  sequence[3].op1 = PACK_OP1 (0, PKA_OP_LDIV, PKA_LIR (LIR_rr, Q_idx), PKA_LIR (LIR_rr, R_idx));
  sequence[3].op2 = PACK_OP2 (PKA_NULL, PKA_LIR (LIR_n, 0));
  sequence[3].ptr = NULL;

  /* unload x[1] */
  sequence[4].op1 = PACK_OP1 (PKA_EOS, PKA_OP_MFLIRI, PKA_LIR (LIR_n, 1), n->size);
  sequence[4].ptr = NULL;

  /* unload y[Q_idx] */
  sequence[5].op1 = PACK_OP1 (PKA_EOS, PKA_OP_MFLIRI, PKA_LIR (LIR_rr, Q_idx), n->size);
  sequence[5].ptr = NULL;

  /* send sequnence */
  while (q_pka_hw_rd_status () & PKA_STAT_BUSY) {
    if ((ctx->status = ctx->q_yield ()) != Q_SUCCESS) goto Q_MONT_INIT_EXIT;
  }
  q_pka_hw_write_sequence (6, sequence);

  /* read result back */
  while (! ((pka_status = q_pka_hw_rd_status ()) & PKA_STAT_DONE)) {
    if (pka_status & PKA_STAT_ERROR) {
      ctx->status = Q_ERR_PKA_HW_ERR;
      goto Q_MONT_INIT_EXIT;
    } else {
      if ((ctx->status = ctx->q_yield ()) != Q_SUCCESS) goto Q_MONT_INIT_EXIT;
    }
  }
  q_pka_hw_wr_status (pka_status);
  q_pka_hw_read_LIR (n->size, rr.limb);
  rr.size = n->size;

  /* read result back */
  while (! ((pka_status = q_pka_hw_rd_status ()) & PKA_STAT_DONE)) {
    if ((ctx->status = ctx->q_yield ()) != Q_SUCCESS) goto Q_MONT_INIT_EXIT;
  }
  q_pka_hw_wr_status (pka_status);
  q_pka_hw_read_LIR (n->size, (mont->np).limb);
  mont->np.neg = 0;

  /* Calcuate Nprime (mont->np) using the extended Euclidean algorithm*/

  q_euclid (ctx, &(mont->np), &lx, n, &rr);

  if ((mont->np).neg == 0) {
    q_SetZero (&lx);
    lx.size = (mont->n).size;
    q_usub (&(mont->np), &lx, &(mont->np));
  } else {
    (mont->np).neg = 0;
  }

  q_copy (n, &mont->n);

  /* Calculate mont->rr = (R ^ 2 mod N) */

  LIR_rr = q_pka_sel_LIR ((mont->n).size * 2);

  /* x[2] = N */
  sequence[0].op1 = PACK_OP1 (0, PKA_OP_MTLIRI, PKA_LIR (LIR_n, 2), (mont->n).size);
  sequence[0].ptr = (mont->n).limb;

  /* y[0] = R mod N */
  sequence[1].op1 = PACK_OP1 (0, PKA_OP_MTLIRI, PKA_LIR (LIR_rr, 0), (mont->n).size);
  sequence[1].ptr = rr.limb;

  /* y[0] = y[0] ^ 2 */
  sequence[2].op1 = PACK_OP1 (0, PKA_OP_LSQR, PKA_LIR (LIR_rr, 0), PKA_LIR (LIR_rr, 0));
  sequence[2].ptr = NULL;

  /* y[0] = y[0] % x[2] */
  sequence[3].op1 = PACK_OP1 (0, PKA_OP_MODREM, PKA_LIR (LIR_rr, 0), PKA_LIR (LIR_rr, 0));
  sequence[3].op2 = PACK_OP2 (PKA_NULL, PKA_LIR (LIR_n, 2));
  sequence[3].ptr = NULL;

  /* unload y[0] */
  sequence[4].op1 = PACK_OP1 (PKA_EOS, PKA_OP_MFLIRI, PKA_LIR (LIR_rr, 0), (mont->n).size);
  sequence[4].ptr = NULL;

  /* send sequnence */
  while (q_pka_hw_rd_status () & PKA_STAT_BUSY) {
    if ((ctx->status = ctx->q_yield ()) != Q_SUCCESS) goto Q_MONT_INIT_EXIT;
  }
  q_pka_hw_write_sequence (5, sequence);

  /* read result back */
  while (! ((pka_status = q_pka_hw_rd_status ()) & PKA_STAT_DONE)) {
    if (pka_status & PKA_STAT_ERROR) {
      ctx->status = Q_ERR_PKA_HW_ERR;
      goto Q_MONT_INIT_EXIT;
    } else {
      if ((ctx->status = ctx->q_yield ()) != Q_SUCCESS) goto Q_MONT_INIT_EXIT;
    }
  }
  q_pka_hw_wr_status (pka_status);
  q_pka_hw_read_LIR ((mont->n).size, (mont->rr).limb);
  (mont->rr).size = (mont->n).size;

  q_free (ctx, &lx);
  q_free (ctx, &rr);

#else /* QLIP_USE_PKA_HW */
  status = q_init (ctx, &c1, 1);
  status += q_init (ctx, &rr, (n->alloc*2+1));
  if (status != Q_SUCCESS) goto Q_MONT_INIT_EXIT;

  q_SetOne (&c1);

  /* R = 2^br */
  /* determine the size of R */
#if 1
  /*
    PKA HW requires R be constructed as follows:
    R = 1 << (32*(n->size)),
    where n->size is number of 32-bit words of n.
  */

  rr.size = 1 + n->size;
  rr.limb[n->size] = 1L;

  br = (n->size) << BITS_FOR_MACHINE_WD;
#endif

#if 0
/*
    The following code constructs R as follows:
    R = 1 << (number of significant bits in n)

		This is a firmware only optimization that can be done.
    However, the result of this optimization would cause
    q_mont_init output to deviate from the PKA implementation.
    In particular, mont_test.c would fail.
	
    Fundamentally, the two approach result in two residue domains.
    The intermediate computation in two domains are different. However,
    if we compute only the final normal result for modexp, the results
    would match when they are converted back from two residue domains.

    ZQI 8/16/2007
*/
  br = q_LeadingOne (n->limb[n->size-1]);

  if (br == MACHINE_WD - 1) {
    rr.size = n->size + 1;
    rr.limb[n->size] = 1L;
  } else {
    rr.size = n->size;
    rr.limb[n->size-1] = (1L << (br+1));
  }

  br += ((n->size-1) << BITS_FOR_MACHINE_WD) + 1;
#endif

  mont->br = br;

  /* R = R mod N */
  if (q_mod (ctx, &rr, &rr, n)) goto Q_MONT_INIT_EXIT;

  /* Ri = R^-1 mod N*/
/* the corresponding PKA call takes the first iteration of q_euclid outside of the main loop,
therefore the corresponding section of q_euclid need to be able to accept non-default last_x and x 
inputs. The firmware-only call doesn't use this method. */
  if (q_modinv (ctx, &mont->rr, &rr, n)) goto Q_MONT_INIT_EXIT;

#ifdef QLIP_DEBUG
  q_print ("mont_init: Ri:", &mont->rr);
#endif /* QLIP_DEBUG */

  /* R * Ri - 1 */
  q_mul_2pn (&rr, &mont->rr, br);
  q_usub (&rr, &rr, &c1);

#ifdef QLIP_DEBUG
  q_print ("mont_init: R * Ri - 1:", &rr);
#endif /* QLIP_DEBUG */

  /* Np = (R * Ri - 1) / N */
  if (q_div (ctx, &mont->np, &rr, n)) goto Q_MONT_INIT_EXIT;

#ifdef QLIP_DEBUG
  q_print ("mont_init: np:", &mont->np);
#endif /* QLIP_DEBUG */

  /* mont->rr = R ^ 2 mod N */
  q_mul_2pn (&rr, &c1, mont->br*2);
  if (q_mod (ctx, &mont->rr, &rr, n)) goto Q_MONT_INIT_EXIT;

  /* need to make sure that np and rr are zero-extended to the size of n */
  if (mont->np.size < mont->n.size) {
    for (i=mont->np.size; i<mont->n.size; i++) {
      mont->np.limb[i] = 0;
    }
    mont->np.size = mont->n.size;
  }

  if (mont->rr.size < mont->n.size) {
    for (i=mont->rr.size; i<mont->n.size; i++) {
      mont->rr.limb[i] = 0;
    }
    mont->rr.size = mont->n.size;
  }

  q_free (ctx, &rr);
  q_free (ctx, &c1);
#endif /* QLIP_USE_PKA_HW */
#endif /* QLIP_USE_GMP */

 Q_MONT_INIT_EXIT:

#ifdef QLIP_DEBUG
  printf ("Exit function %s ()\n", __FUNCTION__);
#endif /* QLIP_DEBUG */

  return (ctx->status);
}

#ifndef REDUCED_RELEASE_CODE_SIZE
/**********************************************************************
 * q_mont_mul ()
 *
 * Description: Montgomery Multiplication
 * Assumptions: a and b are already residue numbers
 **********************************************************************/

q_status_t q_mont_mul (q_lip_ctx_t *ctx,
                       q_lint_t *z,
                       q_lint_t *a,
                       q_lint_t *b,
                       q_mont_t *mont)
{
  q_status_t status = Q_SUCCESS;

#ifdef QLIP_USE_GMP
  uint32_t br;
  mpz_t ma, mb, mn, mnp, mt, mw;
#else
  q_lint_t t, m, u;
  q_size_t st;
#endif

#ifdef QLIP_DEBUG
  printf ("Enter function %s ()\n", __FUNCTION__);
#endif /* QLIP_DEBUG */

#ifdef QLIP_USE_GMP
  br = mont->br;

  mpz_init (ma);
  mpz_init (mb);
  mpz_init (mn);
  mpz_init (mnp);
  mpz_init (mt);
  mpz_init (mw);

  mpz_import (ma, a->size, -1, 4, 0, 0, a->limb);
  mpz_import (mb, b->size, -1, 4, 0, 0, b->limb);
  mpz_import (mn, mont->n.size, -1, 4, 0, 0, mont->n.limb);
  mpz_import (mnp, mont->np.size, -1, 4, 0, 0, mont->np.limb);

  mpz_mul (mt, ma, mb);
  mpz_fdiv_r_2exp (mw, mt, br);
  mpz_mul (mw, mw, mnp);
  mpz_fdiv_r_2exp (mw, mw, br);
  mpz_mul (mw, mw, mn);
  mpz_add (mw, mw, mt);
  mpz_fdiv_q_2exp (mw, mw, br);
  mpz_mod (mt, mw, mn);
  mpz_export (z->limb, &(z->size), -1, 4, 0, 0, mt);

  mpz_clear (ma);
  mpz_clear (mb);
  mpz_clear (mn);
  mpz_clear (mnp);
  mpz_clear (mt);
  mpz_clear (mw);
#else
  /* allocate temporary memory */
  st = a->alloc + b->alloc + mont->np.alloc;
  status = q_init (ctx, &t, st);
  status += q_init (ctx, &m, st);
  status += q_init (ctx, &u, st);
  if (status != Q_SUCCESS) goto Q_MONT_MUL_EXIT;

  if (q_IsOne (a))  q_copy (&t, b);
  else if (q_IsOne (b)) q_copy (&t, a);
  else if (q_mul (ctx, &t, a, b)) goto Q_MONT_MUL_EXIT;

  q_mod_2pn (&u, &t, (uint32_t)mont->br);

  q_mul (ctx, &m, &u, &mont->np);
  q_mod_2pn (&u, &m, (uint32_t)mont->br);

  q_mul (ctx, &m, &u, &mont->n);
  q_uadd (&u, &t, &m);
  q_div_2pn (&t, &u, (uint32_t)mont->br);
  Q_NORMALIZE (t.limb, t.size);

  if ((z->alloc < t.size) && t.limb[t.size-1] != 1L) {
#ifdef QLIP_DEBUG
    q_abort (__FILE__, __LINE__, "QLIP: q_mont_mul insufficient memory for the result!");
#endif
    ctx->status = Q_ERR_DST_OVERFLOW;
    goto Q_MONT_MUL_EXIT;
  }

  if (q_ucmp (&t, &mont->n) > 0) {
    q_usub (&t, &t, &mont->n);
  }

  if (q_copy (z, &t)) goto Q_MONT_MUL_EXIT;

  q_free (ctx, &u);
  q_free (ctx, &m);
  q_free (ctx, &t);

#endif /* QLIP_USE_GMP */

 Q_MONT_MUL_EXIT:

#ifdef QLIP_DEBUG
  printf ("Exit function %s ()\n", __FUNCTION__);
#endif /* QLIP_DEBUG */

  return (ctx->status);
}

/**********************************************************************
 * q_modexp_mont ()
 *
 * Description: Montgomery modulo exponentiation
 * Assumptions: a is already residue numbers
 **********************************************************************/

q_status_t q_modexp_mont (q_lip_ctx_t *ctx,
                          q_lint_t *z,
                          q_lint_t *a,
                          q_lint_t *e,
                          q_mont_t *mont)
{
  int i, j;
  q_size_t es;
  q_limb_ptr_t zp, ep;
  q_lint_t mx;
  int bitset; /* points to the current machine word */

#ifdef QLIP_DEBUG
  printf ("Enter function %s ()\n", __FUNCTION__);
#endif /* QLIP_DEBUG */

  if (q_IsZero (e)) {
    q_SetOne (z);
    goto Q_MODEXP_MONT_EXIT;
  }

  if (!q_IsOdd (&mont->n)) {
#ifdef QLIP_DEBUG
    q_abort (__FILE__, __LINE__, "QLIP: modulus must be an odd number to perform Montgomery modexp!");
#endif
    ctx->status = Q_ERR_GENERIC;
    goto Q_MODEXP_MONT_EXIT;
  }

  zp = z->limb;
  ep = e->limb;
  es = e->size;

  if (q_init (ctx, &mx, a->alloc)) goto Q_MODEXP_MONT_EXIT;
  q_SetOne (&mx);
  if (q_mont_mul (ctx, &mx, &mx, &mont->rr, mont)) goto Q_MODEXP_MONT_EXIT;

  /* LR binary method */
  for (i=es-1; i >= 0; i--) {
    for (j=MACHINE_WD-1; j >= 0; j--) {
      if (q_mont_mul (ctx, &mx, &mx, &mx, mont)) goto Q_MODEXP_MONT_EXIT;
      bitset = ep[i] & (1 << j);
      if (bitset) {
        if (q_mont_mul (ctx, &mx, &mx, a, mont)) goto Q_MODEXP_MONT_EXIT;
      }
    }
  }

  if (q_copy (z, &mx)) goto Q_MODEXP_MONT_EXIT;
  q_free (ctx, &mx);
  Q_NORMALIZE (zp, z->size);

 Q_MODEXP_MONT_EXIT:

#ifdef QLIP_DEBUG
  printf ("Exit function %s ()\n", __FUNCTION__);
#endif /* QLIP_DEBUG */

  return (ctx->status);
}
#endif //REDUCED_RELEASE_CODE_SIZE
