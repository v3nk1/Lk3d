String.prototype.xmlEncode=function(){ return this.replace(/\&/g,"&"+"amp;").replace(/</g,"&"+"lt;").replace(/>/g,"&"+"gt;").replace(/\'/g,"&"+"apos;").replace(/\"/g,"&"+"quot;"); }; String.prototype.bLength=function(){ return encodeURI(this).replace(/%[0-9a-eA-E][0-9a-eA-E]/g,"*").length; }; String.prototype.ulength=function(){ var c,b=0,l=this.length; while(l){ c=this.charCodeAt(--l); b+=(c<128)?1:((c<2048)?2:((c<65536)?3:4)); } return b; }; 