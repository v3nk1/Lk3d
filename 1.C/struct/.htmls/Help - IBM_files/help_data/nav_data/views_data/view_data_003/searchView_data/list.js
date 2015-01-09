var isMozilla=navigator.userAgent.indexOf("Mozilla")!=-1&&parseInt(navigator.appVersion.substring(0,1))>=5; var isIE=navigator.userAgent.indexOf("MSIE")!=-1; var active; var oldActive; function getTRNode(_1){ if(_1.nodeType==3){ return _1.parentNode.parentNode.parentNode; }else{ if(_1.tagName=="A"){ return _1.parentNode.parentNode; }else{ if(_1.tagName=="TD"){ return _1.parentNode; }else{ if(_1.tagName=="TR"){ return _1; }else{ if(_1.tagName=="IMG"){ return _1.parentNode.parentNode.parentNode; }else{ return null; } } } } } }; function getAnchorNode(tr){ var id=tr.id.substring(1); return document.getElementById("a"+id); }; function getNextDown(_4){ var tr=getTRNode(_4); if(tr==null){ return null; } var id=tr.id.substring(1); var _7=1+eval(id); return document.getElementById("a"+_7); }; function getNextUp(_8){ var tr=getTRNode(_8); if(tr==null){ return null; } var id=tr.id.substring(1); var _b=eval(id)-1; if(_b>=0){ return document.getElementById("a"+_b); }else{ return null; } }; function highlightTopic(_c){ if(!_c||(_c.tagName!="A"&&_c.parentNode.tagName!="A")){ return false; } var tr=getTRNode(_c); if(tr!=null){ if(oldActive&&oldActive!=tr){ oldActive.className="list"; var _e=getAnchorNode(oldActive); if(_e){ _e.className=""; } } oldActive=tr; tr.className="active"; var a=getAnchorNode(tr); if(a){ a.className="active"; if(a.onclick){ a.onclick(); } } active=a; return true; } return false; }; function selectTopic(_10){ if(!_10||_10==""){ return; } var _11=document.getElementsByTagName("a"); for(var i=0;i<_11.length;i++){ if(_11[i].href.indexOf(_10+"?toc=")==0||_11[i].href.indexOf(_10+"&toc=")==0||_11[i].href.indexOf(_10+"/?toc=")==0){ highlightTopic(_11[i]); scrollUntilVisible(_11[i],SCROLL_VERTICAL); _11[i].scrollIntoView(true); return true; } } return false; }; function selectTopicById(id){ var _14=document.getElementById(id); if(_14){ highlightTopic(_14); scrollUntilVisible(_14,SCROLL_VERTICAL); return true; } return false; }; function hidePopupMenu(){ var _15=document.getElementById("menu"); if(!_15){ return; } if(_15.style.display=="block"){ _15.style.display="none"; } }; var popupMenuTarget; function showPopupMenu(e){ var x=e.clientX; var y=e.clientY; e.cancelBubble=true; var _19=document.getElementById("menu"); if(!_19){ return; } _19.style.left=(x+1)+"px"; _19.style.top=(y+1)+"px"; _19.style.display="block"; if(isMozilla){ popupMenuTarget=e.target; } }; function showStatus(e){ try{ var _1b; if(isIE){ _1b=window.event.srcElement; }else{ _1b=e.target; } _1b=getTRNode(_1b); if(_1b==null){ window.status=""; return true; } if(!isIE){ e.cancelBubble=false; } var a=getAnchorNode(_1b); var _1d=""; if(isIE){ _1d=a.innerText; }else{ _1d=a.lastChild.nodeValue; } if(a.title&&_1d!=a.title){ _1d+=" - "+a.title; } window.status=_1d; } catch(e){ } return true; }; function clearStatus(){ window.status=""; }; function contextMenuHandler(e){ hidePopupMenu(); if(isIE){ e=window.event; } var _1f=getEventTarget(e); if(!_1f){ return true; } mouseClickHandler(e); if(_1f.tagName=="A"){ active=_1f; }else{ if(_1f.parentNode.tagName=="A"){ active=_1f.parentNode; }else{ return true; } } showPopupMenu(e); return false; }; function mouseClickHandler(e){ if(isIE||e&&e.target&&e.target!=popupMenuTarget){ hidePopupMenu(); } var _21=getEventTarget(e); highlightTopic(_21); }; function focusHandler(e){ if(oldActive){ try{ oldActive.focus(); } catch(e){ } } }; function keyDownHandler(e){ var key; if(isIE){ key=window.event.keyCode; }else{ key=e.keyCode; } if(key!=38&&key!=40){ return true; } var _25=getEventTarget(e); if(!_25){ return; } cancelEventBubble(e); if(key==40){ var _26=getNextDown(_25); highlightTopic(_26); if(_26){ var _27=getTRNode(_26).nextSibling; if(_27!==null){ var _28=_27.nextSibling; if(_28!==null){ scrollUntilVisible(_28,SCROLL_VERTICAL+SCROLL_LEFT); }else{ scrollUntilVisible(_27,SCROLL_VERTICAL+SCROLL_LEFT); } }else{ scrollUntilVisible(_26,SCROLL_VERTICAL+SCROLL_LEFT); } _26.focus(); return false; } }else{ if(key==38){ var _26=getNextUp(_25); highlightTopic(_26); if(_26){ _26.focus(); scrollUntilVisible(getTRNode(_26),SCROLL_VERTICAL+SCROLL_LEFT); return false; } } } return true; }; if(isIE){ document.onclick=mouseClickHandler; document.onkeydown=keyDownHandler; window.onfocus=focusHandler; }else{ document.addEventListener("click",mouseClickHandler,true); document.addEventListener("keydown",keyDownHandler,true); if(isSafari){ document.write("<style type=\"text/css\">"); document.write(".active {background:#B5D5FF;color:#000000;}"); document.write("</style>"); } } 