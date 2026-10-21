#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

struct Instrument {double base; double step; double amplitude;};
Instrument instrument(const std::string& s){
 if(s=="WIN")return {145000,5,460};
 if(s=="WDO")return {5250,0.5,20};
 if(s=="NQ")return {24500,0.25,125};
 if(s=="MNQ")return {24500,0.25,125};
 return {0,0,0};
}
int main(int argc,char** argv){
 std::string symbol=argc>1?argv[1]:"WIN";
 auto ins=instrument(symbol);
 if(ins.step<=0){std::cerr<<"Unsupported symbol";return 2;}
 auto now=std::chrono::system_clock::now();
 auto ms=std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();
 // Intentionally deterministic per second. Demo only; no exchange connection.
 std::mt19937_64 rng(static_cast<std::uint64_t>(ms/1000) ^ static_cast<std::uint64_t>(symbol[0])*1099511628211ULL);
 std::uniform_real_distribution<double> noise(-1.0,1.0);
 auto quant=[&](double x){return std::round(x/ins.step)*ins.step;};
 std::vector<double> points;points.reserve(90);
 double offset=std::sin(static_cast<double>(ms)/120000.0)*ins.amplitude*.3;
 for(int i=0;i<90;i++){
  double phase=static_cast<double>(ms)/40000.0+i*.15;
  double x=ins.base+offset+ins.amplitude*(.45*std::sin(phase)+.28*std::sin(phase*.39)+.13*std::cos(phase*1.6)) +noise(rng)*ins.amplitude*.018;
  points.push_back(quant(x));
 }
 double price=points.back();
 auto [lo,hi]=std::minmax_element(points.begin(),points.end());
 double pressure=std::clamp((points.back()-points[65])/ins.amplitude*100.0,-100.0,100.0);
 double delta=std::round(pressure*82+noise(rng)*300);
 double liquidity=std::clamp(55+noise(rng)*16,0.0,100.0);
 double volatility=(*hi-*lo)/ins.base*100;
 std::cout<<std::fixed<<std::setprecision(4);
 std::cout<<"{\"symbol\":\""<<symbol<<"\",\"price\":"<<price
 <<",\"change\":"<<(price/ins.base-1)*100
 <<",\"pressure\":"<<pressure<<",\"delta\":"<<delta
 <<",\"liquidity\":"<<liquidity<<",\"volatility\":"<<volatility
 <<",\"high\":"<<*hi<<",\"low\":"<<*lo
 <<",\"bid\":"<<price-ins.step<<",\"ask\":"<<price+ins.step
 <<",\"timestamp\":"<<ms
 <<",\"source\":\"DEMONSTRACAO SINTETICA - SEM FEED REAL\",\"series\":[";
 for(size_t i=0;i<points.size();i++){if(i)std::cout<<',';std::cout<<"{\"t\":"<<i<<",\"p\":"<<points[i]<<'}';}
 std::cout<<"],\"candles\":[";
 // Candles fechados demonstrativos: 5 amostras sinteticas por candle.
 // Nao representa barras de tempo de uma bolsa nem volume real.
 double cumulativePV=0.0,cumulativeV=0.0;
 for(int j=0;j<18;j++){
  int a=j*5;double op=points[a],cl=points[a+4];
  double hi=op,lo=op;
  for(int k=a;k<a+5;k++){hi=std::max(hi,points[k]);lo=std::min(lo,points[k]);}
  double vol=100+std::abs(cl-op)/ins.step*4+j*3;
  cumulativePV+=((hi+lo+cl)/3.0)*vol;cumulativeV+=vol;
  if(j)std::cout<<',';
  std::cout<<"{\"t\":"<<j<<",\"o\":"<<op<<",\"h\":"<<hi<<",\"l\":"<<lo<<",\"c\":"<<cl<<",\"v\":"<<vol<<",\"vwap\":"<<cumulativePV/cumulativeV<<"}";
 }
 std::cout<<"]}";
}
