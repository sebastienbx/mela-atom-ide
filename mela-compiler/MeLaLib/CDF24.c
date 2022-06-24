#include "CDF24.h"


static const int32_t SQRT2_NUM = 239L;
static const int32_t SQRT2_DEN = 169L;
static const int32_t A = 3L;
static const int32_t B = 19L;
static const int32_t C = 64L;


/******************************************************************************
 * Subfunctions
 ******************************************************************************/

int32_t _long_mult_and_div (int32_t x, int32_t num, int32_t den) {
    int32_t rem;
    // 3 comparisons, 2 affectations, 1 modulus, 2 multiplications, 2 divisions, 1 addition
    if (x == 0) return 0;
    if (num == 0) return 0;
    if (den == 0) {
        if ( ((x > 0) && (num > 0)) || ((x < 0) && (num < 0)) ) {
            return INT32_MAX;
        }
        return INT32_MIN;
    }
    if (num < 0L) {
        // 2 affectations, 2 additions
        num = -num;
        x = -x;
    }
    if (x < 0L) {
        rem = -x % den;
        x /= den;
        return x * num - (num * rem) / den;
    }
    rem = x % den;
    x /= den;
    return x * num + (num * rem) / den;
}





/******************************************************************************
 * Integer implementation
 ******************************************************************************/

static inline void _cdf24I32_round (array_i32_t* x, int lx, cdf24_i32_t* cdf24) {
    size_t n, m;
    cdf24->d[0] = x->data[1] - (x->data[0] + x->data[2])/2;
    cdf24->d[1] = x->data[3] - (x->data[2] + x->data[4])/2;
    cdf24->d[2] = x->data[5] - (x->data[4] + x->data[6])/2;
    if (cdf24->edges_correction) {
        /* Haar transform: a[0] = x[0] + d[0]/2 */
        cdf24->a[0] = x->data[0] + cdf24->d[0]/2;
        /* CDF[2,2] transform: a[1] = x[1] + (d[0] + d[1])/4 */
        cdf24->a[1] = x->data[2] + (cdf24->d[0] + cdf24->d[1])/4;
    } else {
        cdf24->a[0] = x->data[0];
        cdf24->a[1] = x->data[2];
    }

    for (n = 2U; n < lx - 2U; n ++) {
        m = (n << 1) + 3;
        cdf24->d[n+1] = x->data[m] - (x->data[m-1U] + x->data[m+1U])/2;
        cdf24->a[n] = x->data[m - 3] - _long_mult_and_div (cdf24->d[n-2U] + cdf24->d[n+1U], A, C)
                + _long_mult_and_div (cdf24->d[n-1U] + cdf24->d[n+0U], B, C);
    }

    if (cdf24->edges_correction) {
        /* Haar transform: d[end] = x[end] - x[end - 1] */
        cdf24->d[lx-1] = x->data[(lx<<1)-1] - x->data[(lx<<1)-2];
        /* CDF[2,2] transform: a[n] = x[2*n - 1] + (d[n-1] + d[n])/4 */
        cdf24->a[lx-1] = x->data[(lx<<1)-2] + (cdf24->d[lx-1U] + cdf24->d[lx-2U])/4;
    } else {
        cdf24->d[lx-1] = x->data[(lx<<1)-1];
        cdf24->a[lx-1] = x->data[(lx<<1)-2];
    }
    if (lx > 3) {
        cdf24->a[lx-2] = x->data[(lx<<1)-4]
                   - _long_mult_and_div (cdf24->d[lx-4U] + cdf24->d[lx-1U], A, C)
                   + _long_mult_and_div (cdf24->d[lx-3U] + cdf24->d[lx-2U], B, C);
    }
}

/* Normalization improved by A. Sukhovich: instead of multiplying each
 * round approximation and dividing details per sqrt(2), we're
 * multiplying approximation per 2 for even rounds, and details are
 * divided per sqrt(2) each odd rounds. Greatly improves accuracy.
 */
/* TODO is fusion with approx and detail loop doable ? */
static inline void _cdf24I32_sort (array_i32_t* x, int lx, int k, cdf24_i32_t* cdf24) {

    size_t n;
    if (cdf24->normalized) {
        // With nromalization trick
        if (k % 2) {
            for (n = 0U; n < lx; n++) {
                x->data[n]      = 2 * cdf24->a[n];
                x->data[lx + n] = cdf24->d[n];
            }
        } else {
            for (n = 0U; n < lx; n++) {
                x->data[n]      = cdf24->a[n];
                x->data[lx + n] = _long_mult_and_div (cdf24->d[n], SQRT2_DEN, SQRT2_NUM);
            }
        }
        /* Without the normalization trick
        for (n = 0U; n < lx; n++) {
            x[n]      = long_mult_and_div (_a[n], SQRT2_NUM, SQRT2_DEN);
            x[lx + n] = long_mult_and_div (_d[n], SQRT2_DEN, SQRT2_NUM);
        }
        */
    } else {
        for (n = 0U; n < lx; n++) {
            x->data[n]      = cdf24->a[n];
            x->data[lx + n] = cdf24->d[n];
        }
    }
}



void cdf24I32 (array_i32_t* x, cdf24_i32_t* cdf24) {
    int i, k;
    int lx = x->len;
    for (i = 0; i < cdf24->len/2; i++) {
        cdf24->a[i] = 0;
        cdf24->d[i] = 0;
    }
    for (k = 0U; k < cdf24->K; k++) {
        lx >>= 1;
        _cdf24I32_round (cdf24, x, lx);
        _cdf24I32_sort (cdf24, x, lx, k);
    }
    if ((cdf24->K % 2) && (cdf24->normalized)) {
        for (k = 0U; k < lx; k++) {
            x->data[k] = _long_mult_and_div (x->data[k], SQRT2_NUM, SQRT2_DEN);
        }
    }
}



int cdf24ScalesPowerI32 (array_i32_t* x, size_t n0, size_t n1, array_i32_t* scales_pow, cdf24_i32_t* cdf24) {

    size_t k, n, n0k, n1k;
    uint64_t tmp, index_diff;

    /* Evaluate the power in each detail scale */
    for (k = 1UL; k <= cdf24->K; k++) {
        /* translate index */
        n0k = (x->len + n0) >> k;
        n1k = (x->len + n1) >> k;
        tmp = 0ULL;
        for (n = n0k; n < n1k; n++) {
            tmp += ((uint64_t) (x->data[n] > 0 ? x->data[n] : -x->data[n]));
        }
        index_diff = (n1k - n0k);
        if (cdf24->normalized) {
            tmp /= index_diff;
            if (tmp > UINT32_MAX) {
                scales_pow->data[k - 1UL] = UINT32_MAX;
            } else {
                scales_pow->data[k - 1UL] = tmp;
            }
        } else {
            if (tmp > UINT32_MAX) {
                tmp /= index_diff;
                tmp *= 1 << ((k - 1) >> 1);
                tmp += ((tmp % index_diff) * (1 << ((k - 1) >> 1))) / index_diff;
                if (k % 2) {
                    tmp *= SQRT2_DEN;
                    tmp /= SQRT2_NUM;
                }
                if (tmp > UINT32_MAX) {
                    scales_pow->data[k - 1UL] = UINT32_MAX;
                } else {
                    scales_pow->data[k - 1UL] = tmp;
                }
            } else {
                scales_pow->data[k - 1UL] = _long_mult_and_div (tmp, 1 << ((k - 1) >> 1),
                                                         n1k - n0k);
                if (k % 2) {
                    scales_pow->data[k - 1UL] = _long_mult_and_div (scales_pow->data[k - 1UL],
                                                             SQRT2_DEN, SQRT2_NUM);
                }
            }
        }
    }
    return 0;
}






















/******************************************************************************
 * Float implementation
 ******************************************************************************/

static const float32_t SQRT2f = 1.414213562;
static const float32_t Af = 3.;
static const float32_t Bf = 19.;
static const float32_t Cf = 64.;

static inline void _cdf24F32_round (array_f32_t* x, int k, cdf24_f32_t* cdf24) {
    size_t n, m;
    int lx = x->len >> k;
    cdf24->d[0] = x->data[1] - (x->data[0] + x->data[2])/2;
    cdf24->d[1] = x->data[3] - (x->data[2] + x->data[4])/2;
    cdf24->d[2] = x->data[5] - (x->data[4] + x->data[6])/2;
    if (cdf24->edges_correction) {
        /* Haar transform: a[0] = x[0] + d[0]/2 */
        cdf24->a[0] = x->data[0] + cdf24->d[0]/2;
        /* CDF[2,2] transform: a[1] = x[1] + (d[0] + d[1])/4 */
        cdf24->a[1] = x->data[2] + (cdf24->d[0] + cdf24->d[1])/4;
    } else {
        cdf24->a[0] = x->data[0];
        cdf24->a[1] = x->data[2];
    }

    for (n = 2U; n < lx - 2U; n ++) {
        m = (n << 1) + 3;
        cdf24->d[n+1] = x->data[m] - (x->data[m-1U] + x->data[m+1U])/2;
        cdf24->a[n] = x->data[m - 3]
                        - (cdf24->d[n-2U] + cdf24->d[n+1U])*Af/Cf
                        + (cdf24->d[n-1U] + cdf24->d[n+0U])*Bf/Cf;
    }

    if (cdf24->edges_correction) {
        /* Haar transform: d[end] = x[end] - x[end - 1] */
        cdf24->d[lx-1] = x->data[(lx<<1)-1] - x->data[(lx<<1)-2];
        /* CDF[2,2] transform: a[n] = x[2*n - 1] + (d[n-1] + d[n])/4 */
        cdf24->a[lx-1] = x->data[(lx<<1)-2] + (cdf24->d[lx-1U] + cdf24->d[lx-2U])/4;
    } else {
        cdf24->d[lx-1] = x->data[(lx<<1)-1];
        cdf24->a[lx-1] = x->data[(lx<<1)-2];
    }
    if (lx > 3) {
        cdf24->a[lx-2] = x->data[(lx<<1)-4]
                            - (cdf24->d[lx-4U] + cdf24->d[lx-1U])*Af/Cf
                            + (cdf24->d[lx-3U] + cdf24->d[lx-2U])*Bf/Cf;
    }
}

/* Normalization improved by A. Sukhovich: instead of multiplying each
 * round approximation and dividing details per sqrt(2), we're
 * multiplying approximation per 2 for even rounds, and details are
 * divided per sqrt(2) each odd rounds. Greatly improves accuracy.
 */
/* TODO is fusion with approx and detail loop doable ? */
static inline void _cdf24F32_sort (array_f32_t* x, int k, cdf24_f32_t* cdf24) {
    size_t n;
    int lx = x->len >> k;
    if (cdf24->normalized) {
        // With normalization trick
        if (k % 2) {
            for (n = 0U; n < lx; n++) {
                x->data[n]      = 2 * cdf24->a[n];
                x->data[lx + n] = cdf24->d[n];
            }
        } else {
            for (n = 0U; n < lx; n++) {
                x->data[n]      = cdf24->a[n];
                x->data[lx + n] = cdf24->d[n]/SQRT2f;
            }
        }
        /* Without the normalization trick
        for (n = 0U; n < lx; n++) {
            x[n]      = long_mult_and_div (_a[n], SQRT2_NUM, SQRT2_DEN);
            x[lx + n] = long_mult_and_div (_d[n], SQRT2_DEN, SQRT2_NUM);
        }
        */
    } else {
        for (n = 0U; n < lx; n++) {
            x->data[n]      = cdf24->a[n];
            x->data[lx + n] = cdf24->d[n];
        }
    }
}



void cdf24F32 (array_f32_t* x, cdf24_f32_t* cdf24) {
    int i;
    for (i = 0; i < cdf24->len/2; i++) {
        cdf24->a[i] = 0;
        cdf24->d[i] = 0;
    }
    for (i = 1; i <= cdf24->K; i++) {
        _cdf24F32_round (x, i, cdf24);
        _cdf24F32_sort (x, i, cdf24);
    }
    if ((cdf24->K % 2) && (cdf24->normalized)) {
        for (i = 0U; i < (x->len >> cdf24->K); i++) {
            x->data[i] = x->data[i]*SQRT2f; // TODO: why to multiply by sqrt2?
        }
    }
}



int cdf24ScalesPowerF32 (array_f32_t* x, size_t n0, size_t n1, array_f32_t* scales_pow, cdf24_f32_t* cdf24) {

    size_t k, n, n0k, n1k;
    uint64_t index_diff;
    float32_t tmp;

    /* Evaluate the power in each detail scale */
    for (k = 1; k <= cdf24->K; k++) {
        /* translate index */
        n0k = (x->len + n0) >> k;
        n1k = (x->len + n1) >> k;
        tmp = 0.;
        for (n = n0k; n < n1k; n++) {
            tmp += x->data[n] > 0 ? x->data[n] : -x->data[n];
        }
        index_diff = (n1k - n0k);

        // If sdc4 normalize
        //tmp /= index_diff;
        //scales_pow->data[k - 1] = tmp;

        // else
        scales_pow->data[k - 1] = tmp * (float32_t)(1 << ((k - 1) >> 1)) / (float32_t)(n1k - n0k);
        if (k % 2) {
            scales_pow->data[k - 1] = scales_pow->data[k - 1UL]*SQRT2f;
        }

        /*
        if (cdf24->normalized) {
            tmp /= index_diff;
            scales_pow->data[k - 1] = tmp;
        } else {
            scales_pow->data[k - 1] = tmp * (float32_t)(1 << ((k - 1) >> 1)) / (float32_t)(n1k - n0k);
            if (k % 2) {
                scales_pow->data[k - 1] = scales_pow->data[k - 1UL]*SQRT2f;
            }
        }
         */

    }
    return 0;
}
