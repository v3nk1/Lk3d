dojo.declare("vcc.comment.CommentContent",null,{ContentViewFrame:window.top.HelpFrame.ContentFrame.ContentViewFrame,icMode:window.top.HelpFrame.ContentFrame.document.getElementById("vccFrames").noResize,markedElementIDs:[],isCommentAble:function(){ var _1=this.getUrl(); if(null==_1||_1=="about:blank"){ return false; }else{ return this.ContentViewFrame&&this.ContentViewFrame.pageID&&this.ContentViewFrame.pageID!=-1; } },_extractParam:function(_2,_3){ try{ var _4=_2.indexOf(_3+"=")+_3.length+1; if(_4==_3.length){ return null; } var _5=_2.indexOf("&",_4); if(_5<0){ _5=_2.length; } if(_5>_4){ return _2.substring(_4,_5); }else{ return null; } } catch(e){ console.debug(e); return null; } },getUrlHtmlID:function(){ var _6=this.getUrl(); if(_6){ return this._extractParam(_6,"htmlid"); }else{ return null; } },getUrlCommentID:function(){ var _7=this.getUrl(); if(_7){ return this._extractParam(_7,"cid"); }else{ return null; } },getPageID:function(){ try{ if(this.ContentViewFrame.pageID){ return this.ContentViewFrame.pageID; }else{ var _8=this.ContentViewFrame.document.location.href; if(_8=="about:blank"){ return -1; } var _9=_8.indexOf("pageid")+7; if(_9>7){ var _a=_8.indexOf("&",_9); var _b=_8.substring(_9,_a); return _b; }else{ return -1; } } } catch(e){ return -1; } },getPluginVersion:function(){ return this.ContentViewFrame.pluginVersion; },getPrifix:function(){ return this.ContentViewFrame.prefixValue; },isLatestVersion:function(){ if(this.ContentViewFrame.latestVersion==this.ContentViewFrame.pluginVersion){ return true; } return false; },getContentLocale:function(){ if(this.ContentViewFrame.contentLocale){ return this.ContentViewFrame.contentLocale; }else{ return "en_US"; } },setUrl:function(_c){ this.ContentViewFrame.location=_c; },getUrl:function(){ if(this.ContentViewFrame&&this.ContentViewFrame.location){ return this.ContentViewFrame.location.href; }else{ return null; } },selectFragmentAndDisplayComment:function(_d){ if(this.ContentViewFrame.content&&this.ContentViewFrame.content.selectFragmentAndDisplayComment){ this.ContentViewFrame.content.selectFragmentAndDisplayComment(_d,true); } },selectFragment:function(_e){ if(this.ContentViewFrame.content&&this.ContentViewFrame.content.selectFragment){ this.ContentViewFrame.content.selectFragment(_e,true); } },_showMarkers:function(_f){ if(this.ContentViewFrame.content._marker){ this.ContentViewFrame.content._marker.showMarkers(_f); } },_hideMarkers:function(){ if(this.ContentViewFrame.content._marker){ this.ContentViewFrame.content._marker.hideAllMarkers(); } },toICMode:function(_10){ var _11=this.ContentViewFrame.content; if(_11){ if(_11._highlighter){ _11._highlighter.clearHighlight(); } this._hideMarkers(); if(_11.disableClickHandler){ _11.disableClickHandler(); } } this.icMode=true; },toReviewMode:function(_12){ var _13=this.ContentViewFrame.content; if(_13){ var _14=commentView.getCommentedHtmlIDs(); this._hideMarkers(); this._showMarkers(_14); if(_13.disableClickHandler&&_12){ _13.disableClickHandler(); } if(_13.enableClickHandler){ _13.enableClickHandler(); } } this.icMode=false; },refreshMode:function(){ if(this.icMode){ this.toICMode(true); }else{ this.toReviewMode(true); } },getSelection:function(){ var _15=this.ContentViewFrame.content; if(_15){ return this.ContentViewFrame.content.currentSelection; }else{ return null; } },createSelection:function(_16){ return FreeSelect.create(_16); },isParsed:function(){ var _17=this.ContentViewFrame.window.location.href.toLowerCase(); if(_17.indexOf(".html")<0&&_17.indexOf(".htm")<0){ return true; } if(!this.ContentViewFrame.content||!this.ContentViewFrame.content._docParser){ return false; } return this.ContentViewFrame.content._docParser.parsed; }}); 