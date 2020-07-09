"use strict";

(function()
{
    main();
}());


function main(){
	var skipBtn = document.getElementById("skipBtn");
	skipBtn.style.visibility = 'visible';

	var videoContainer = document.getElementById("video");
	var videoSource = document.getElementById("videoSource");

	var ref2 = "Animations/AnimLevel1-2.mp4";
	var ref3 = "Animations/AnimLevel2-3.mp4";
	var ref4 = "Animations/Victory.mp4";


	var text = getCookie("playVideo");
	console.log("Texto recebido de play: " + text);
	var current = 0;
	if(text!=""){
		var number = parseInt(text);
		switch(number){
			case 1:
				videoContainer.play();
				current = 1;
				break;
			case 2:
				current = 2;
				videoSource.setAttribute('src', ref2);
				videoContainer.load();
				videoContainer.play();
				break;
			case 3:
				current=3;
				videoSource.setAttribute('src', ref3);
				videoContainer.load();
				videoContainer.play();
				break;
			case 6:
				videoSource.setAttribute('src', ref4);
				videoContainer.load();
				videoContainer.play();
				current=6;
				break;
			default: break;
		}
	}
	else{
		alert("Video reference not received");
		/*skipBtn.style.visibility = 'visible';
		introVideo.style.visibility = 'visible';
		introVideo.play();*/
	}

	var state = function(ev){
		goBackFunction(current);
	}

	videoContainer.addEventListener("ended",goBackFunction);
	/*video1_2.addEventListener("ended",goBackFunction);
	video2_3.addEventListener("ended",goBackFunction);
	victoryVideo.addEventListener("ended",goBackFunction);
*/
	skipBtn.addEventListener("click",goBackFunction);
}
function teste(){
	alert('Saltar has been pressed!');
}
function goBackFunction(number){
	window.parent.postMessage({
		state: "endVideo"},'*');
}


function setCookie(cname,cvalue,exdays){
	var d = new Date();
	d.setTime(d.getTime() + (exdays * 24 * 60 * 60 * 1000));
	var expires = "expires"+d.toUTCString();
	document.cookie = cname + "=" + cvalue + ";" + expires + ";path=/";
}

function getCookie(cname){
    var name = cname + "=";
    var decodedCookie = decodeURIComponent(parent.document.cookie);
    
    var ca = decodedCookie.split(";");
    for(var i = 0; i < ca.length; i++) {
        var c = ca[i];
        while (c.charAt(0) == ' ') {
          c = c.substring(1);
    	}
	    if (c.indexOf(name) == 0) {
	    	return c.substring(name.length, c.length);
	    }
    }
    return "";
}