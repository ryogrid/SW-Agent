#define SIGMA 6

#define _dt	0.037
#define DP	6
#define MP	2

extern IplImage *imgSrc; // Source Image

#define draw_cross( center, color, d)	\
				cvLine( imgSrc, cvPoint( center.x - d, center.y - d), \
											cvPoint( center.x + d, center.y + d), color, 1, CV_AA, 0);	\
				cvLine( imgSrc, cvPoint( center.x + d, center.y - d), \
											cvPoint( center.x - d, center.y + d), color, 1, CV_AA, 0);

#define	calc_point( x, y)	cvPoint( cvRound(x), cvRound(y) )

//float _dt=0.33;

float A[] = { 1, 0, _dt,  0, _dt*_dt/2,  		0,
							0, 1,  0, _dt,	 	 0,  _dt*_dt/2,
							0, 0,  1,  0,		 	_dt,				0,
							0, 0,  0,  1,			0,			 _dt,
							0, 0,  0,  0,			1,				0,
							0, 0,  0,  0,     0,        1};
CvRNG rng;
