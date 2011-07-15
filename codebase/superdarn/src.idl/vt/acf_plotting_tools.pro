;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; COPYRIGHT:
; Copyright (C) 2011 by Virginia Tech
;
; Permission is hereby granted, free of charge, to any person obtaining a copy
; of this software and associated documentation files (the "Software"), to deal
; in the Software without restriction, including without limitation the rights
; to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
; copies of the Software, and to permit persons to whom the Software is
; furnished to do so, subject to the following conditions:
;
; The above copyright notice and this permission notice shall be included in
; all copies or substantial portions of the Software.
;
; THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
; IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
; FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
; AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
; LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
; OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
; THE SOFTWARE.
;
;
; MODIFICATION HISTORY:
; Written by AJ Ribeiro 07/15/2011
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
pro plot_single_acf,l0p,noise,pflg,lflg,pos,lagnums,acfs,good_lags,ymax

		ptitle = 'Original Raw ACF'+'		'+$
							'Lag 0 Power = '+strtrim(round(l0p),2)+'		'+$
							'Noise = '+strtrim(round(noise),2)+'		'+$
							'Pwr Flg = '+strtrim(round(pflg),2)+'		'+$
							'Lag Flg = '+strtrim(round(lflg),2)
		loadct,0
		plot,findgen(1),findgen(1),/nodata,xrange=[0,max(lagnums(*))],yrange=[-1.0*ymax,ymax],$
					xstyle=1,ystyle=1,xthick=4,ythick=4,pos=pos,/noerase,thick=2.,$
					yticklen=-.01,title=ptitle,charthick=3,charsize=.75
		loadct,34
		usersym,cos(S),sin(S)
		plots,0,acfs(0,0)+noise,psym=8,col=150
		for j=0,mplgs-1 do begin
			if(good_lags(j)) then p = 2 else p = 8
			plots,lagnums(j),acfs(j,0),psym=p,col=250
			plots,lagnums(j),acfs(j,1),psym=p,col=50
		endfor
		plots,lagnums(*),acfs(*,0),linestyle=0,col=250,thick=2
		plots,lagnums(*),acfs(*,1),linestyle=0,col=50,thick=2
end