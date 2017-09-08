#ifndef _H_ALGORITHMIC_IMAGE_H
#define _H_ALGORITHMIC_IMAGE_H

double ai_mandel2(double x0, double y0);
double ai_julia2(double x0, double y0, double c_real=-0.8, double c_imagine=0.156); 
/* Xianshun says:
 in ai_julia2, parameter to try for c:
 c = -0.8 + 0.156i
 c = 0.687 + 0.312i
 */

double ai_mandel3(double x0, double y0);
double ai_mandel4(double x0, double y0);

double ai_julia3(double x0, double y0, double c_real=0.6, double c_imagine=0.55); 
/* Xianshun says:
	in ai_julia3, parameter to try for c:
	c = 0.6+0.55i
*/

double ai_julia4(double x0, double y0, double c_real=0.6, double c_imagine=0.55); 
/* Xianshun says:
	in ai_julia4, parameter to try for c:
	c = 0.6+0.55i
*/

double ai_julia5(double x0, double y0, double c_real=0.8, double c_imagine=0.6); 
/* Xianshun says:
	in ai_julia5, parameter to try for c:
	c = 0.8+0.6i
*/

#endif
