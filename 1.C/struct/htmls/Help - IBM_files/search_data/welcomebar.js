function setAccountInfo(_1,_2){ if(null!=_2&&"null"!=_2&&""!=_2){ document.getElementById("helloLabel").innerHTML=dojo.string.substitute(templateHello,{username:_2}); }else{ document.getElementById("helloLabel").innerHTML=dojo.string.substitute(templateHello,{username:_1}); } if(document.getElementById("logon")){ document.getElementById("logon").style.display="none"; } document.getElementById("logout").style.display="block"; }; function resetAccountInfo(){ document.getElementById("helloLabel").innerHTML=dojo.string.substitute(templateHello,{username:guest}); if(document.getElementById("logon")){ document.getElementById("logon").style.display="block"; } if(document.getElementById("logout")){ document.getElementById("logout").style.display="none"; } }; 