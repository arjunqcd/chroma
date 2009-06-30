#include <xmmintrin.h>
#include <pmmintrin.h>

inline
void ord_cxmayf_kernel(int lo, int hi, int my_id, ord_cxmayf_arg* arg)
{
  REAL32* x_ptr = &(arg->x_ptr[lo]);
  REAL32* y_ptr = &(arg->y_ptr[lo]);

  REAL32 a_re = arg->a_re;
  REAL32 a_im = arg->a_im;

  int len = hi - lo;
  __m128 av_re = _mm_set_ps(a_re, a_re, a_re, a_re);
  __m128 av_im = _mm_set_ps(-a_im,a_im,-a_im, a_im);


  for(int count=0; count < len; count+=4) { 
    __m128 xv = _mm_load_ps(&x_ptr[count]);
    __m128 yv = _mm_load_ps(&y_ptr[count]);
    __m128 yv2 = _mm_shuffle_ps( yv,yv, 0xb1);
    
    __m128 t1 = _mm_mul_ps(av_re, yv);
    __m128 t2 = _mm_sub_ps(xv, t1);
    __m128 t3 = _mm_mul_ps(av_im, yv2);
    xv = _mm_add_ps(t2, t3);
    
    _mm_store_ps(&x_ptr[count], xv);
  }
     

}
