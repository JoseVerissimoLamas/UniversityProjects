"use scrict";


const totPages = 3;



(function(){	
	window.addEventListener("load", main);

}());

class Player{
	constructor(name, age,score,lastLevel){
		this.name = name;
		this.age = age;
		this.coins = 0;
		this.score = score;
		this.lastLevel = lastLevel;
	}
}

function main()

{

	var pages = ["menu","levels2","video"];

	showMenu("menu");

	var players = new Array();
	var current = null; //Reference to the current player

	var mH = function(ev){
		current = messageHandler(ev,players,current);
	}
	window.addEventListener("message", mH);

	var frm = document.getElementsByTagName("iframe")[0];
	frm.style.overflowX = 'hidden';
	frm.style.overflowY = 'hidden';

	if(!verifyCookie("allPlayers")) setCookie("allPlayers","",10);
	else{
		var text = getCookie("allPlayers");
		console.log("There are initial players!!!");
		updatePlayers(text,players);
	}	

}


//---- Navegação e gestão de janelas

//Verificar a existência de jogadores já existentes
function updatePlayers(text,players){
	var lines = text.split("*");
	for (let i = 0; i <= lines.length-2; i++) {
		console.log("Current line: " + lines[i]);
		var [name,age,score,lastLevel] = lines[i].split('/');
		var novo = new Player(name,age,score,lastLevel);
		players.push(novo);
		console.log(players[i].name + "|" + players[i].age + "|" + players[i].score + "|" + players[i].lastLevel);
	}

}


function showPage(pageName)
{

	//carregar página na frame e enviar mensagem para a página logo que esteja carregada (frameLoadHandler)

	var frm = document.getElementsByTagName("iframe")[0];

	frm.src = "" + pageName + ".html";
	console.log("NAme of page|" + pageName + "|");
}



function hidePage(pageNum)  //não é necessário (excepto se páginas diferentes tivessem zonas de navegação diferentes)
{

	var frm = document.getElementsByTagName("iframe")[0];

	frm.src = "";
}


function showMenu(ev)
{

	var frm = document.getElementsByTagName("iframe")[0];

	var frmName = frm.src;

	hidePage();

	showPage("menu");

}

function showLevels(ev){
	var frm = document.getElementsByTagName("iframe")[0];

	var frmName = frm.src;

	hidePage();

	showPage("levels2");
}

//Evento e documento, ver diferenças

function verifyCookie(name){
	if(getCookie(name) == ""){
		return 1;
	}
	return -1;
}

function setCookie(cname,cvalue,exdays){
	var d = new Date();
	d.setTime(d.getTime() + (exdays * 24 * 60 * 60 * 1000));
	var expires = "expires"+d.toUTCString();
	document.cookie = cname + "=" + cvalue + ";" + expires + ";path=/";
}

function orderPlayers(players){
	console.log("Players were suposed to being order!!!!!!!!");
	
	console.log("A ordenar");
	for (let i = 0; i < players.length; i++) {
		for (let k = i+1; k < players.length; k++) {
			if(players[k].score > players[i].score){
				var aux = players[k];
				players[k] = players[i];
				players[i] = aux;
			}
		}
	}

	console.log("Ordenados:");
	for (var i = 0; i <=players.length-1; i++) {
		console.log("Name: " + players[i].name + "/Score: " + players[i].score);
	}	

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
function showVideo(ev,current){
	var frm = document.getElementsByTagName("iframe")[0];

	var frmName = frm.src;

	hidePage();
	var message = ""+current;
	console.log("!!!!!Current inside video: " + current);
	setCookie("playVideo",message,10);
	showPage("video");
}

function messageHandler(ev,players,current){
	var flag = true;
	if(ev.data.state == "endmenu"){
		//console.log("Current Object Players");
		console.log("Players present: ");
		for(let i = 0;i<players.length;i++){
			//console.log("Name: " + players[i].name + " Age: " + players[i].age);
			console.log("Name: " + players[i].name);
			if(players[i].name === ev.data.player.name){
				flag = false;
				current = players[i];
			}
		}
		console.log("End of players present");
		if(flag){
			var name = ev.data.player.name;
			var age = ev.data.player.age;
			var score = 0;
			var novo = new Player(name,age,score,0);
			players.push(novo);
			var message = "new"+"/"+name+"/"+age+"/"+"0"+"/"+"0";
			setCookie("currentPlayer",message,10);
			console.log("CurrentPlayer updated with new!");

			alert('Foi criado um novo jogador!');

			var text = getCookie("allPlayers");
			text += name + "/"+ age + "/" + score + "/" + "0" + "*";

			console.log("Final do menu, indo para o jogo em si");
			
			setCookie("allPlayers",text,10);


			var salut = "Olá: " + name + " com: " + age + " anos";
			salut += "\nVais ser redirecionado para o primeiro nivel";
			salut += "\nApós o video de introdução!"
            alert(salut);

            showVideo(ev,1);
			
			/*showLevels(ev);*/
		}
		else{
			//If the player exists, we will pass that information to all frames
			var message = "exist"+"/"+current.name+"/"+current.age+"/"+current.score+"/"+current.lastLevel;
			console.log("Verificação de nivel: " + current.lastLevel);
			setCookie("currentPlayer",message,10);
		}
		
	}
	else if(ev.data.state === "decision"){
		if(ev.data.decision == "no"){
			var text = getCookie("currentPlayer");
			var sms = text.split("/");
			var message = sms[0] + "/" + sms[1] + "/" + sms[2] + "/" + sms[3] +"/" +"0";
			console.log("Message: " + message);
			setCookie("currentPlayer",message,10);
			showLevels(ev);
		}
		else if(ev.data.decision == "yes"){
			console.log("Entra no sitio certo!!");
			showLevels(ev);
		}
		else{
			alert("Infelizemente não nos é possivel recuperar o seu progresso. \nPor favor recomece de incio");
			showLevels(ev);
		}
	}
	else if(ev.data.state == "orderPlayers"){
		orderPlayers(players);/*
		var text = "";
		console.log("Suposed players in back page:");
		for (let i = 0; i <= players.length-1; i++) {
			console.log("i: " + i + "->"+players[i].name + " /" + players[i].score)
			text += players[i].name + "/"+players[i].age+"/"+players[i].score+"*";
		}
		setCookie("allPlayers",text,10);*/
		console.log("End of order players");

	}
	else if(ev.data.state == "endlevels"){
		//alert("Level 5 has ended");
		showVideo(ev,6);
		alert("O jogo chegou ao fim!\nConsulte o seu ranking através do menu");
		showMenu(ev);

	}
	else if(ev.data.state == "backToMenu"){
		console.log("Voltou ao menu, da pausa?");
		showMenu(ev);
	}
	else if(ev.data.state == "updateData"){
		var nome = ev.data.player.name;
		var score = parseInt(ev.data.player.score);
		var lastLevel = parseInt(ev.data.player.lastLevel);

		console.log("Dados recebidos:");
		console.log("Score: " + score);
		console.log("Último nivel: " + lastLevel);

		for (let i = 0; i <= players.length-1; i++) {
			if(players[i].name === nome){
				players[i].score = score;
				players[i].lastLevel = lastLevel;
			}
		}
		orderPlayers(players);
		var text = "";
		for (let i = 0; i <= players.length-1; i++) {
			text += players[i].name + "/"+players[i].age+"/"+players[i].score+"/"+ players[i].lastLevel+"*";
		}
		setCookie("allPlayers",text,10);
		console.log("Texto: " + text);

		/*var message = "" + (lastLevel+1);
		console.log("Video passado: " + message);
		setCookie("playVideo",message,10);*/
		console.log("Player.repeat: " + ev.data.player.repeat);
		if(ev.data.player.repeat == "true"){
			showLevels(ev);
		}
		else if(lastLevel!=3 && lastLevel!=4){
			showVideo(ev,lastLevel+1);
		}
	}
	else if(ev.data.state == "endVideo"){
		showLevels(ev);
	}

}
