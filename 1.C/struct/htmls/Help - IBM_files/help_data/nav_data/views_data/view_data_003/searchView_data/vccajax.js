var isMozilla=navigator.userAgent.indexOf("Mozilla")!=-1&&parseInt(navigator.appVersion.substring(0,1))>=5; var isIE=navigator.userAgent.indexOf("MSIE")!=-1; var reply=null; function AJAX(){ }; AJAX.RequestCreators=[function(){ return new XMLHttpRequest(); },function(){ return new ActiveXObject("Msxml2.XMLHTTP"); },function(){ return new ActiveXObject("Microsoft.XMLHTTP"); }]; AJAX.CreatRequest=null; AJAX.newRequest=function(){ if(AJAX.CreatRequest!=null){ return AJAX.CreatRequest(); } for(var i=0;i<AJAX.RequestCreators.length;i++){ try{ var _2=AJAX.RequestCreators[i]; var _3=_2(); if(_3!=null){ AJAX.CreatRequest=_2; return _3; } } catch(e){ continue; } } }; AJAX.post=function(_4,_5,_6,_7){ var _8=AJAX.newRequest(); _8.onreadystatechange=function(){ try{ if(_8.readyState==4){ if(_8.status==200){ _6(_8.responseXML); }else{ if(_7){ _7(_8.status,_8.statusText); }else{ _6(null); } } } } catch(e){ if(_7){ _7(500,e); }else{ _6(null); } } }; _8.open("POST",_4); _8.setRequestHeader("Content-Type","application/x-www-form-urlencoded"); _8.send(AJAX.encodeFormData(_5)); }; AJAX.encodeFormData=function(_9){ var _a=[]; var _b=/%20/g; for(var _c in _9){ var _d=_9[_c].toString(); var _e=encodeURIComponent(_c).replace(_b,"+")+"="+encodeURIComponent(_d).replace(_b,"+"); _a.push(_e); } return _a.join("&"); }; AJAX.ROOTPATH=null; AJAX.getRootPath=function(){ if(AJAX.ROOTPATH!=null){ return AJAX.ROOTPATH; }else{ var _f=window.top.location.href; var _10=_f.indexOf("?"); if(_10!=-1){ _f=_f.substring(0,_10); } var _11=_f.lastIndexOf("/"); AJAX.ROOTPATH=_f.substring(0,_11)+"/"; return AJAX.ROOTPATH; } }; function getElementText(_12,_13){ var _14=""; try{ _14=_12.getElementsByTagName(_13)[0].firstChild.nodeValue; } catch(e){ } return _14; }; AJAX.getTrimedValue=function(id){ var _16=document.getElementById(id); return vccUtils.trimString(_16.value); }; 