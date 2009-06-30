// 32 BIT Version. Use vector length of 4 (guaranteed OK for LatticeDirac Fermion)
// for easy vectorization (with suitably good compiler).

#include <xmmintrin.h>
#include <emmintrin.h>

inline
void ord_ib_rxupdate_kernel_real32(int lo, int hi, int my_id, ib_rxupdate_arg<REAL32>* a)
{

  
  REAL32* s = &(a->s_ptr[lo]);
  REAL32* t = &(a->t_ptr[lo]);
  REAL32* z = &(a->z_ptr[lo]);
  REAL32* r = &(a->r_ptr[lo]);
  REAL32* x = &(a->x_ptr[lo]);

  REAL32 om_re = a->omega_re;
  REAL32 om_im = a->omega_im;

  __m128 om_re_vec = _mm_set_ps(om_re, om_re, om_re, om_re);
  __m128 om_im_vec = _mm_set_ps(-om_im, om_im, -om_im, om_im);
  __m128 mom_im_vec = _mm_set_ps(om_im, -om_im, om_im, -om_im);

  int len = hi - lo;
  for(int count = 0; count < len; count+=4) { 
    /*
     * r[count]   = s[count]   - om_re*t[count]   + om_im*t[count+1];
     * r[count+1] = s[count+1] - om_re*t[count+1] - om_im*t[count];
     * r[count+2] = s[count+2] - om_re*t[count+2] + om_im*t[count+3];
     * r[count+3] = s[count+3] - om_re*t[count+3] - om_im*t[count+2];
     */
    

    __m128 t_vec = _mm_load_ps(&t[count]);
    __m128 s_vec = _mm_load_ps(&s[count]);

    __m128 tmpv1 = _mm_mul_ps(om_re_vec, t_vec);

    __m128 tmpv2 = _mm_shuffle_ps(t_vec, t_vec, 0xb1);
    __m128 r_vec = _mm_sub_ps(s_vec, tmpv1);

    tmpv1 = _mm_mul_ps(om_im_vec,tmpv2);
    r_vec = _mm_add_ps(r_vec, tmpv1);
    _mm_store_ps(&r[count], r_vec);


    

    /*
      x[count]   += om_re*s[count]   - om_im*s[count+1] + z[count];
      x[count+1] += om_re*s[count+1] + om_im*s[count]   + z[count+1];
      x[count+2] += om_re*s[count+2] - om_im*s[count+3] + z[count+2];
      x[count+3] += om_re*s[count+3] + om_im*s[count+2] + z[count+3];
    */

    /* x[ ... ] */
    __m128 xvec = _mm_load_ps(&x[count]);

    /* z[ ... ] */
    __m128 zvec = _mm_load_ps(&z[count]);


    tmpv1 = _mm_mul_ps(om_re_vec, s_vec);
    xvec = _mm_add_ps(xvec, tmpv1);
    
    tmpv2 = _mm_shuffle_ps(s_vec, s_vec, 0xb1);
    xvec = _mm_add_ps(xvec,zvec);

    tmpv1 = _mm_mul_ps(mom_im_vec,tmpv2);
    xvec = _mm_add_ps(xvec, tmpv1);

    _mm_store_ps(&x[count], xvec);

  }  
}



// 64 BIT Version. Use vector length of 2 (guaranteed OK for Complex Numbers)
// for easy vectorization (with suitably good compiler). Can do function 
// overloading so no need to change kernel name

inline
void ord_ib_rxupdate_kernel_real64(int lo, int hi, int my_id, ib_rxupdate_arg<REAL64>* a)
{

  
  REAL64* s = &(a->s_ptr[lo]);
  REAL64* t = &(a->t_ptr[lo]);
  REAL64* z = &(a->z_ptr[lo]);
  REAL64* r = &(a->r_ptr[lo]);
  REAL64* x = &(a->x_ptr[lo]);

  REAL64 om_re = a->omega_re;
  REAL64 om_im = a->omega_im;

  
  int len = hi - lo;
  __m128d om_re_vec = _mm_set_pd(om_re, om_re);
  __m128d om_im_vec = _mm_set_pd(-om_im, om_im);
  __m128d mom_im_vec = _mm_set_pd(om_im, -om_im);

  for(int count = 0; count < len; count+=2) { 
    
    /*
    r[count]   = s[count]   - om_re*t[count]   + om_im*t[count+1];
    r[count+1] = s[count+1] - om_re*t[count+1] - om_im*t[count];
    */
    __m128d svec = _mm_load_pd(&s[count]);
    __m128d tvec = _mm_load_pd(&t[count]);

    __m128d tmpv2 = _mm_mul_pd(om_re_vec,tvec);
    __m128d rvec = _mm_sub_pd(svec, tmpv2);


    __m128d tmpv1 = _mm_shuffle_pd(tvec,tvec,0x1);
    tmpv2 = _mm_mul_pd(om_im_vec,tmpv1);
    rvec = _mm_add_pd(rvec, tmpv2);
    _mm_store_pd(&r[count], rvec);



    /*
      x[count]   += om_re*s[count]   - om_im*s[count+1] + z[count];
      x[count+1] += om_re*s[count+1] + om_im*s[count]   + z[count+1];
    
    */
    __m128d xvec = _mm_load_pd(&x[count]);
    __m128d zvec = _mm_load_pd(&z[count]);

    tmpv1 = _mm_mul_pd(om_re_vec, svec);
    xvec = _mm_add_pd(xvec,tmpv1);

    tmpv2 = _mm_shuffle_pd(svec,svec,0x1);
    xvec = _mm_add_pd(xvec,zvec);

    tmpv1 = _mm_mul_pd(mom_im_vec, tmpv2);
    xvec = _mm_add_pd(xvec,tmpv1);

    _mm_store_pd(&x[count],xvec);

  }  
}



