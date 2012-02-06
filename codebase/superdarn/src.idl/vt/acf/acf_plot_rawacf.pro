;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;+
;	NAME:
; 	acf_plot_rawacf
;
; PURPOSE:
; 	plots a RAWACF, and possibly LM fitting results
;
; CATEGORY:
; 	Graphics
;
; CALLING SEQUENCE:
;		acf_plot_rawacf,re,im,mplgs,lagnums,badlags,position,ref=ref,imf=imf,lmheader=lmheader
;
;
;	INPUTS:
;		re: 				an array of size mplgs with real lags of the ACF
;		im: 				an array of size mplgs with imaginary lags of ACF
;		mplgs:			number of lags in the acf
;		lagnums:		an array of size mplgs containing the lag numbers of the ACF
;		badlags:		an array of size mplgs with flags indicating bad lags (2=good, 1=more_badlags,0=badlags)
;		position:		position to put the panel
;
; OPTIONAL INPUTS:
;		ref:				the real part of the LM fitted ACF
;		imf:        the imaginary part of the LM fitted ACF
;		lmheader:		title for LMFIT plot
;
; KEYWORD PARAMETERS:
;
; EXAMPLE:
;
; OUTPUT:
;
;
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
; Written by AJ Ribeiro 02/06/2012
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
pro acf_plot_rawacf,re,im,mplgs,lagnums,badlags,position,ref=ref,imf=imf,lmheader=lmheader

	S = findgen(17)*(!PI*2./16.)
	usersym,cos(S),sin(S),/fill

	ymax = max(abs([re(*),im(*)]))*1.1

	;create the axes
	plot,findgen(1),findgen(1),/nodata,xrange=[0,max(lagnums)],yrange=[-1.0*ymax,ymax],$
			xstyle=1,ystyle=1,xthick=3,ythick=3,pos=position,/noerase,thick=3.,$
			yticklen=-.01,title='Original Raw ACF',charthick=3,charsize=.6,xtitle='lag',$
			ytitle='level'

	;annotate the plot
	xyouts,.87,.85,'Real',/normal,charsize=.7,charthick=3.
	xyouts,.87,.82,'Imag',/normal,charsize=.7,charthick=3.
	xyouts,.89,.79,'badlags',/normal,charsize=.7,charthick=3.
	xyouts,.89,.76,'more_badlags',/normal,charsize=.7,charthick=3.
	loadct,34
	plots,.85,.855,psym=8,col=250,/normal
	plots,.85,.825,psym=8,col=50,/normal
	plots,.85,.795,psym=6,col=250,/normal
	plots,.875,.795,psym=6,col=50,/normal
	plots,.85,.765,psym=5,col=250,/normal
	plots,.875,.765,psym=5,col=50,/normal

	;plot the ACF
	for i=0,mplgs-1 do begin
		if(badlags(i) eq 0) then p = 6
		if(badlags(i) eq 1) then p = 5
		if(badlags(i) eq 2) then p = 8
		plots,lagnums(i),re(i),psym=p,col=250
		plots,lagnums(i),im(i),psym=p,col=50
	endfor
	plots,lagnums(*),re(*),linestyle=0,col=250,thick=3
	plots,lagnums(*),im(*),linestyle=0,col=50,thick=3

	;go back to davit ct
	init_colors

end