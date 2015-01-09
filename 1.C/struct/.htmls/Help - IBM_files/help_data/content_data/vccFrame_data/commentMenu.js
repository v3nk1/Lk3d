dojo.declare("vcc.comment.CommentMenu",null,{setAddButtonsDisabled:function(_1){ try{ if(dijit&&dijit.byId){ if(dijit.byId("addcomment_btn")&&dijit.byId("addcomment_btn")){ dijit.byId("addcomment_btn").setAttribute("disabled",_1); } } } catch(e){ console.dir(e); } },showDisabledTip:function(_2,_3){ var _4=dojo.byId("tipSpan"); var _5=dojo.byId("addcomment_btn"); var _6=dojo.byId("commentDisabledTip"); if(_4&&_5){ if(_2){ _5.style.display="none"; _4.style.display="inline"; _6.innerHTML=_3; }else{ _4.style.display="none"; _5.style.display="inline"; } _4.innerHTML="<img style='vertical-align:middle' src='images/cd_element.gif'/>&nbsp;"+nlsStrings.LABEL_COMMENT_ON_TOPIC; } },localeDisabledTip:function(_7){ var _8=dojo.byId("localetipSpan"); var _9=dojo.byId("localeSwitch_button"); var _a=dojo.byId("localeSelectTip"); if(_8&&_9){ if(_7){ _9.style.display="none"; _8.style.display="inline"; _a.innerHTML=nlsStrings.LABEL_LOCALE_TIP; }else{ _8.style.display="none"; _9.style.display="inline"; } } },displayCommentAmount:function(_b){ var _c=document.getElementById("comment_amount"); var _d=nlsStrings.LABEL_COMMENTS_AMOUNT; _c.innerHTML=dojo.string.substitute(_d,{amount:_b}); },setSelectLocaleDisabled:function(_e){ try{ if(dijit&&dijit.byId){ dijit.byId("localeSwitch_button").setAttribute("disabled",_e); } } catch(e){ console.dir(e); } },initLocaleOptions:function(){ var _f=commentContent.getContentLocale(); var _10=commentContent.getPageID(); var _11=commentContent.getPluginVersion(); dojo.xhrGet({url:AJAX.getRootPath()+"PageLocaleServlet?pageid="+_10+"&version="+_11+"&uniquerequestid="+new Date().getTime(),handleAs:"json",load:function(_12,_13){ if(null!=_12){ commentMenu.fillLocaleInfo(_12.items); } }}); },fillLocaleInfo:function(_14){ var _15=_14.length; if(0==_15){ this.setSelectLocaleDisabled(true); this.localeDisabledTip(true); }else{ var _16=4; this.setSelectLocaleDisabled(false); this.localeDisabledTip(false); document.getElementById("defaultLocale_div").innerHTML="<a href='javascript:void(0);' title=\""+nlsStrings.LABEL_LOCALE_DEFAULT_TIP+"\" onClick='commentMenu.changeLocaleEvent("+null+");'>"+"<img src='../vcc/images/back.gif'/><span>"+nlsStrings.LABEL_LOCALE_BACK+"</span></a>"; var _17=(_15<_16)?_15:_16; var _18=document.getElementById("localeContent_root"); var _19=_18.parentNode; _19.removeChild(_18); _18=document.createElement("tbody"); _18.id="localeContent_root"; var row=document.createElement("tr"); for(var i=0;i<_17;i++){ var col=document.createElement("td"); if(i!=_17-1){ col.className="localeCol nonLastLocaleCol"; }else{ col.className="localeCol"; } col.innerHTML="<ul id='localeUL"+i+"'></ul>"; row.appendChild(col); } _18.appendChild(row); _19.appendChild(_18); for(var j=0;j<_15;j++){ var _1e=j%_17; var _1f=document.getElementById("localeUL"+_1e); var _20=_14[j].abbr; var _21=_14[j].name; var _22=_14[j].amount; _1f.innerHTML+="<li><a href='javascript:void(0);' onClick='javascript: commentMenu.changeLocaleEvent(\""+_20+"\");'>"+_21+"   ["+_22+"]</a></li>"; } } },changeLocaleEvent:function(_23){ var url=commentContent.getUrl(); var _25=url.indexOf("?"); if(_25>=0){ url=url.substring(0,_25); } if(_23&&_23.length>0&&"null"!=_23){ url=url+"?locale="+_23; } commentContent.setUrl(url); }}); 