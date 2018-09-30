/**\brief
 *
 * =====================================================================================
 *
 *       Filename:  dm_sim.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  11/02/2017 04:19:43 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  K.J.Lee (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdio.h>
#include <sedge.h>
using namespace std;
extern "C"{
#include "cn.h"
}
 struct Warp_Sun t0;
  struct Thick t1;
  struct Thin t2;
  struct Spiral t3;
  struct GC t4;
  struct Gum t5;
  struct LB t6;
  struct LI t7;
  struct FB t8;
  struct LMC t9;
  struct Dora t10;
  struct SMC t11;
char dirname[] = "./";

int main(int argc, char * argv[])
{
	double ne = 0;
  double ne0 = 0;
  double ne1 = 0;
  double ne2 = 0;
  double ne3 = 0;
  double ne4 = 0;
  double ne5 = 0;
  double ne6 = 0;
  double ne7 = 0;
  double ll, bb, hh;

  double R_g = 0;
  double gd = 0;
  double rr = 0;

  double z_warp, zz_w, R_warp, theta_warp, theta_max;
  R_warp = 8400; // in parsec
  theta_max = 0.0; // in +x direction
	double xx=0,yy=0,zz=0;
  int WGN = 0;
  int WLB = 0;
  int WLI = 0;
  int WFB = 0;

m_3=0;
  ww=1;
  m_5=0;
  m_6=0;
  m_7=0;

  ymw16par(&t0, &t1, &t2, &t3, &t4, &t5, &t6, &t7, &t8, &t9, &t10, &t11, dirname);

	SEQUENCE vx,vy,vz, vtheta, vphi, veta;
	LoadFromTextFile(vx,Se_CMD_Key_Val(argv, argc, "-x"));
	LoadFromTextFile(vy,Se_CMD_Key_Val(argv, argc, "-y"));
	LoadFromTextFile(vz,Se_CMD_Key_Val(argv, argc, "-z"));
	LoadFromTextFile(vtheta,Se_CMD_Key_Val(argv, argc, "-t"));
	LoadFromTextFile(vphi,Se_CMD_Key_Val(argv, argc, "-f"));
	LoadFromTextFile(veta,Se_CMD_Key_Val(argv, argc, "-eta"));

	double dl = 0.003;
	SEQUENCE vL = Series(0,dl, 2*20);
	SEQUENCE vne=Zeros(vL.n);
	SEQUENCE vdm=Zeros(vx.n);
	for (long int iind=0;iind<vx.n;iind++)
	{
		for (long int jind=0;jind<vL.n;jind++)
		{
	xx=vx(iind)+vL(jind)*sin(vtheta(iind))*cos(vphi(iind));
	yy=vy(iind)+vL(jind)*sin(vtheta(iind))*sin(vphi(iind));
	zz=vz(iind)+vL(jind)*cos(vtheta(iind));
	xx=xx*1000.;
	yy=yy*1000.;
	zz=zz*1000.;
  rr = sqrt(xx * xx + yy * yy);
  if(rr < R_warp){
  zz_w = zz;
  }else{
  theta_warp = atan2(yy, xx);
  z_warp = t0.Gamma_w * (rr-R_warp) * cos(theta_warp - theta_max);
  zz_w = zz - z_warp;
  }
  
  thick(xx, yy, zz_w, &gd, &ne1, rr, t1);
  thin(xx, yy, zz_w, gd, &ne2, rr, t2);
  spiral(xx, yy, zz_w, gd, &ne3, rr, t3, dirname);
  galcen(xx, yy, zz, &ne4, t4);
  gum(xx, yy, zz, &ll, &ne5, t5);
  localbubble(xx, yy, zz, &ll, &bb, &ne6, &hh, t6);
  nps(xx, yy, zz, &ne7, &WLI, t7);
  fermibubble(xx, yy, zz, &WFB);

  if(WFB == 1){
    ne1 = t8.J_FB * ne1;
  }
  ne0 = ne1 + MAX(ne2, ne3);

  if(hh > 110){       /* Outside LB */
    if(ne6 > ne0 && ne6 > ne5){
      WLB = 1;
    }else{
      WLB = 0;
    }
  }else{            /* Inside LB */
    if(ne6 > ne0){
      WLB = 1;
    }else{
      ne1 = t6.J_LB * ne1;
      ne0 = ne1 + MAX(ne2,ne3);
      WLB = 0;
    }
  }
  if(ne7 > ne0){     /* Loop I */
    WLI = 1;
  }else{
    WLI = 0;
  }        
  if(ne5 > ne0){     /* Gum Nebula */
    WGN = 1;
  }else{
    WGN = 0;
  }

  /* Galactic ne */
  ne = (1-WLB)*((1-WGN)*((1-WLI)*(ne0+ne4)+WLI*ne7)+WGN*ne5)+WLB*ne6;
	vne(jind)=ne;
		}
		vdm(iind)=Sum(vne)*veta(iind)*1000*dl;
		if (iind % 1000==0)
		{
			cout<<iind<<endl;
			SaveToTextFile(vdm, Se_CMD_Key_Val(argv, argc, "-out"));
		}
	}
	SaveToTextFile(vdm, Se_CMD_Key_Val(argv, argc, "-out"));
}
double ne_spiral(double xx, double yy, double zz)
{
  char dirname[] = "./";

  double ne3 = 0;

  double gd = 0;
  double rr = 0;

  double z_warp, zz_w, R_warp, theta_warp, theta_max;
  R_warp = 8400; // in parsec
  theta_max = 0.0; // in +x direction

  struct Warp_Sun t0;
  struct Thick t1;
  struct Thin t2;
  struct Spiral t3;
  struct GC t4;
  struct Gum t5;
  struct LB t6;
  struct LI t7;
  struct FB t8;
  struct LMC t9;
  struct Dora t10;
  struct SMC t11;

  ymw16par(&t0, &t1, &t2, &t3, &t4, &t5, &t6, &t7, &t8, &t9, &t10, &t11, dirname);
  rr = sqrt(xx * xx + yy * yy);
  if(rr < R_warp){
  zz_w = zz;
  }else{
  theta_warp = atan2(yy, xx);
  z_warp = t0.Gamma_w * (rr-R_warp) * cos(theta_warp - theta_max);
  zz_w = zz - z_warp;
  }
  
  spiral(xx, yy, zz_w, gd, &ne3, rr, t3, dirname);

  return ne3;

}
