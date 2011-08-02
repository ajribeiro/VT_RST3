;****************************************************************************
PRO radar_info,stid,glat,glon,mlat,mlon,oneletter,threeletter,name,$
              RAD_ABBR=rad_abbr,CAP_FLG=cap_flg,STID_FLG=stid_flg
;
; This fills the arrays passed to it with radar info for all of the radars,
; unless the rad_abbr keyword is set, in which case only the information for
; the requested radar is outputted
;
; OUTPUTS:
;   stid        --  the array to be filled with station ID numbers
;   glat        --  the array to be filled with the geographic latitude of radars
;   glon        --  the array to be filled with the geographic longitude of radars
;   mlat        --  the array to be filled with the magnetic latitude of radars
;   mlon        --  the array to be filled with the magnetic longitude of radars
;   oneletter   --  the array to be filled with the one letter abbreviations of radars
;   threeletter --  the array to be filled with the three letter abbreviations of radars
;
; KEYWORDS:
;   rad_abbr    --  assign a three letter abbreviation of a radar to this keyword
;                   to be returned one-element arrays with only the info of the
;                   requested radar
;   cap_flg     --  set this flag to get the one letter radar abbreviations capitalized
;
; 06/11/2009
;*******************************************************************************

  ;initialize the arrays
  nrad        = 27
  stid        = intarr(nrad)
  glat        = fltarr(nrad)
  glon        = fltarr(nrad)
  mlat        = fltarr(nrad)
  mlon        = fltarr(nrad)
  oneletter   = strarr(nrad)
  threeletter = strarr(nrad)

  ;populate the arrays
  stid        = [33,1,4,10,40,64,3,15,16,7,6,9,65,11,5,2,8,13,12,14,18,32,205,204,206,207,0]
  glat        = [37.10,53.32,-75.52,62.32,43.33,68.42,49.39,-49.22,58.68,$dfgsdfjgkl;jdfg
                57.60,53.98,63.77,62.82,-71.68,52.16,54.80,63.86,-69.00,$
                -69.00,-43.40,-46.51,37.93,38.86,38.86,43.271,43.271,37.10]
  glon        = [-77.95,-60.46,-26.63,26.61,143.61,-133.50,-82.32,70.14,-156.65,$
                -152.20,-122.59,-20.54,-93.11,-2.85,-106.53,-66.80,-22.02,39.58,$
                39.58,147.20,168.38,-75.47,-99.39,-99.39,-120.358,-120.358,-77.95]
  oneletter   = ['i','g','h','f','i','i','k','p','c','a','b','e','i','d','t',$
                's','w','n','j','r','u','i','z','z','z','z','z']
  threeletter = ['bks','gbr','hal','han','hok','inv','kap','ker','ksr','kod',$
                'pgr','pyk','rkn','san','sas','sch','sto','sye','sys','tig','unw','wal',$
                'fhe','fhw','cvw','cve','tst']
  name =        ['Blackstone','Goose Bay','Halley Bay','Hankalsalmi','Hokkaido','Inuvik','Kapuskasing','ker','ksr','kod',$
                'Prince George','pyk','rkn','san','sas','sch','sto','sye','sys','tig','unw','wal',$
                'Fort Hays East','Fort Hays West','Christmas Valley West','Christmas Valley East','Test Radar']

  ;sort the arrays by station id #
  glat        = glat[SORT(stid)]
  glon        = glon[SORT(stid)]
  oneletter   = oneletter[SORT(stid)]
  threeletter = threeletter[SORT(stid)]
  name = name[SORT(stid)]
  stid        = stid[SORT(stid)]

  ;populate the magnetic coordinate arrays
  for i=0,nrad-1 do begin
;     mpos = cnvcoord(glat(i),glon(i),100.)
;     mlat(i) = mpos(0)
;     mlon(i) = mpos(1)
  endfor

  ;if we only want one radar, reform the arrays
  if(keyword_set(rad_abbr)) then begin
    index=-1
    for i=0,nrad-1 do begin
      if(threeletter(i) eq rad_abbr) then begin
        glat        = reform(glat(i:i))
        glon        = reform(glon(i:i))
        mlat        = reform(mlat(i:i))
        mlon        = reform(mlon(i:i))
        oneletter   = reform(oneletter(i:i))
        threeletter = reform(threeletter(i:i))
        name        = reform(name(i:i))
        stid        = reform(stid(i:i))
        index       = i
        break
      endif
    endfor
    if(index eq -1) then print,"radar abbreviation not recognized"
  endif

  ;if we only want one radar, reform the arrays
  if(keyword_set(stid_flg)) then begin
    index=-1
    for i=0,nrad-1 do begin
      if(stid(i) eq stid_flg) then begin
        glat        = reform(glat(i:i))
        glon        = reform(glon(i:i))
        mlat        = reform(mlat(i:i))
        mlon        = reform(mlon(i:i))
        oneletter   = reform(oneletter(i:i))
        threeletter = reform(threeletter(i:i))
        name        = reform(name(i:i))
        stid        = reform(stid(i:i))
        index       = i
        break
      endif
    endfor
    if(index eq -1) then print,"radar abbreviation not recognized"
  endif


  ;if we want capital one-letter abbreviations
  if(keyword_set(cap_flg)) then begin
    for i=0,n_elements(oneletter)-1 do begin
      oneletter(i) = strupcase(oneletter(i))
    endfor
  endif

END



