; readfitacf.pro
; ==============
; Author: R.J.Barnes
; 
; $License$
;
; A Simply demonstration program for reading rawacf files


pro readfitacf

; Open the fit index file and load it into the inx structure 

;   openr,inp,'data/fitacf/test.fitinx',/GET_LUN,/STDIO,/SWAP_IF_BIG_ENDIAN
;   s=FitLoadInx(inp,inx)
;   free_lun,inp

; Open the raw file for read only 
 
  inp=FitOpen('/data/fit/20100401.fhe.fitex',/read)

  openw,out,'~/20100401.fhe.txt',/get_lun
 

;  Search for a specific time in the file
	data = dblarr(150,5)
  while FitRead(inp,prm,fit) ne -1 do begin
		if(prm.time.hr eq 4 AND (prm.time.mt eq 46 OR prm.time.mt eq 47)) then begin
			n = 0
			for i=0,prm.nrang-1 do begin
				if(fit.qflg(i) ne 0) then begin
					yrsc=TimeYMDHMSToYrSec(prm.time.yr,prm.time.mo,prm.time.dy,prm.time.hr,prm.time.mt,prm.time.sc)
					pos1 = rbpos(i+1,height=300,beam=prm.bmnum,lagfr=prm.lagfr,smsep=prm.smsep, $
								rxrise=prm.rxrise,station=prm.stid,year=prm.time.yr,yrsec=yrsc,/GEO,/center)
					pos2 = rbpos(i+2,height=300,beam=prm.bmnum,lagfr=prm.lagfr,smsep=prm.smsep, $
								rxrise=prm.rxrise,station=prm.stid,year=prm.time.yr,yrsec=yrsc,/GEO,/center)

					getazm,pos1(0),pos1(1),pos2(0),pos2(1),azm
					data(n,0) = pos1(0)
					data(n,1) = pos1(1)
					data(n,2) = azm
					data(n,3) = fit.v(i)
					data(n,4) = fit.w_l(i)
					n = n+1
				endif
			endfor
			printf,out,prm.stid,prm.time.yr,prm.time.mo,prm.time.dy,prm.time.hr,prm.time.mt,prm.time.sc,n
			for i=0,n-1 do begin
				printf,out,data(i,0),data(i,1),data(i,2),data(i,3),data(i,4)
			endfor
    endif
  endwhile
  free_lun,inp


  close,out
  free_lun,out





; date/time   N points
; 1   lat  lon   azm  vlos
; .
; .
; .
; N


end


