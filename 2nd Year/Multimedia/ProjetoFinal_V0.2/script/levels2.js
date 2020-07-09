(function(){
	window.addEventListener('load', (main));
}());

function main(){

	var map_1 = returnMap("map/lvl1.txt");
	var map_2 = returnMap("map/lvl2.txt");
	var map_3 = returnMap("map/lvl3.txt");
	var map_4 = returnMap("map/lvl4.txt");
	var map_5 = returnMap("map/lvl5.txt");

	//The canvas
	var canvas = document.querySelector("canvas");
	var ctx = canvas.getContext("2d");

	var lvls = [];

	var sound1,sound2,sound3,sound4,sound5,soundOver,coinSound;
	[sound1,sound2,sound3,sound4,sound5,soundOver,coinSound] = getSoundReferences();

	var lvl = new Level(ctx, canvas, "Level/nivel1_final.png", 1);
	lvl.loadLevel(map_1,sound1,coinSound);
	lvls.push(lvl);

	lvl = new Level(ctx, canvas, "Level/nivel2_final.png", 2);
	lvl.loadLevel(map_2,sound2,coinSound);
	lvls.push(lvl);

	lvl = new Level(ctx, canvas ,"Level/nivel3_final.png", 3);
	lvl.loadLevel(map_3,sound3,coinSound);
	lvls.push(lvl);

	lvl = new Level(ctx, canvas ,"Level/nivel4_final.png", 4);
	lvl.loadLevel(map_4,sound4,coinSound);
	lvls.push(lvl);

	lvl = new Level(ctx, canvas ,"Level/nivel5_final.png", 3);
	lvl.loadLevel(map_5,sound5,coinSound);
	lvls.push(lvl);

	var yesBttn,noBttn,pauseBox;
	var buttons = new Array();
	[yesBttn,noBttn,pauseBox,yesBttnOver,noBttnOver,gameBox] = getPauseButtons(lvls);
	buttons.push(yesBttn);
	buttons.push(noBttn);
	buttons.push(pauseBox);
	buttons.push(yesBttnOver);
	buttons.push(noBttnOver);
	buttons.push(gameBox);

	//Get info on the current player
	var text = getCookie("currentPlayer");
	console.log("Text:" + text);
	var info = text.split("/");

	/*
	info[0] = exist or new
	info[1] = name
	info[2] = age
	info[3] = score
	info[4] = lastLevel
	*/

	var nivel = parseInt(info[4]);

	//If player has already finish the game!
	if(nivel == 5){
		alert('Parabéns!\nJá completou todos os niveis!\nIrá ser redirecionado para o nivel 1');
		nivel = 1;
	}

	//Should never get inside of the if
	if(isNaN(nivel)){console.log("Ocorreu um erro com a passagem de informação");}
	for (var i = info.length - 1; i >= 0; i--) {
		console.log(info[i] + "|");
	}
	var age = parseInt(info[2]);
	var score = parseInt(info[3]);
	//console.log("Info: " + info);
	var player = new Player(info[1],age,score,nivel);
	var i = 0;
	//console.log("Last Level: " + lastLevel);
	if(player.lastLevel == 0) i=0;
	else{
		i = nivel;
	}

	if(nivel!=0){
		var mensagem = "O último nivel registado foi o: " + nivel;
		mensagem+= "\nProsseguirá para o: " + (nivel+1);
		alert(mensagem);
	}


	var reqID = 0;

	var text = getCookie("SoundVolume");
	var sound = parseFloat(text);
	lvls[i].coinSound.volume = sound;
	text = getCookie("MusicVolume");
	sound = parseFloat(text);
	lvls[i].music.volume = sound;

	lvls[i].music.play();
	animation(i, reqID,player, lvls,buttons);
}

function yesOverHandler(lvls,noBttnOver,yesBttnOver,gameOverBox){
	for (var i = 0; i <= lvls.length-1; i++) {
		lvls[i].pause3.pause3 = false;
		lvls[i].pause.pause = !lvls[i].pause.pause;
		lvls[i].buggy.sourceX = 10;
	 	lvls[i].buggy.sourceY = 0;
	 	lvls[i].buggy.sourceWidth = 50;
	 	lvls[i].buggy.sourceHeight = 102;
	 	lvls[i].buggy.width = 50;
	 	lvls[i].buggy.height = 100;
	 	lvls[i].pause.pause = false;
	 	lvls[i].buggy.x = lvls[i].buggy.respawnX;
 		lvls[i].buggy.y = lvls[i].buggy.respawnY;
	}

	/*noBttnOver.style.visibility = "hidden";
	yesBttnOver.style.visibility = "hidden";
	gameOverBox.style.visibility = "hidden";*/

}

function getPauseButtons(lvls){
	var yesBttn = document.getElementById("yes");
	var noBttn = document.getElementById("no");
	var pauseBox = document.getElementById("pauseBox");
	var noBttnOver = document.getElementById('noGameOver');
	var yesBttnOver = document.getElementById('yesGameOver');
	var gameOverBox = document.getElementById('gameOverBox');

	yesBttn.style.visibility = 'hidden';
	noBttn.style.visibility = 'hidden';
	pauseBox.style.visibility = 'hidden';
	noBttnOver.style.visibility = 'hidden';
	yesBttnOver.style.visibility = 'hidden';
	gameOverBox.style.visibility = 'hidden';

	yesBttn.addEventListener("click",yesHandler);
	var nH = function(ev){
		noHandler(lvls,yesBttn,noBttn,pauseBox);
	}
	noBttn.addEventListener("click",nH);

	var yOH = function(ev){
		yesOverHandler(lvls);
	}

	yesBttnOver.addEventListener("click",yOH);
	noBttnOver.addEventListener("click",noOverHandler);

	return [yesBttn,noBttn,pauseBox,yesBttnOver,noBttnOver,gameOverBox];
}

function noOverHandler(){
	alert('Atenção:\nIrá perder o progresso do nivel em que se encontra!');
	window.parent.postMessage(
    {
        state: "backToMenu",
    }, '*');
}



function getSoundReferences(){
	var sound1 = document.getElementById("level1Music");
	var sound2 = document.getElementById("level2Music");
	var sound3 = document.getElementById("level3Music");
	var sound4 = document.getElementById("level4Music");
	var sound5 = document.getElementById("level5Music");
	var soundOver = document.getElementById("level6Music");
	var coinSound = document.getElementById("hitSBox");
	return [sound1,sound2,sound3,sound4,sound5,soundOver,coinSound];
}

function yesHandler(){
	alert('Atenção:\nIrá perder o progresso do nivel em que se encontra!');
	window.parent.postMessage(
    {
        state: "backToMenu",
    }, '*');
}

function noHandler(lvls,yesBttn,noBttn,pauseBox){
	for (var i = 0; i <= lvls.length-1; i++) {
		lvls[i].pause2.pause2 = false;
		lvls[i].pause.pause = !lvls[i].pause.pause;
		//levels[i].pause2.pause2
	}
	yesBttn.style.visibility = 'hidden';
	noBttn.style.visibility = 'hidden';
	pauseBox.style.visibility = 'hidden';
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

function returnMap(mapFile) {
	var allText = getText(mapFile);
	var allTextAux = allText;

	var lines = allText.split("\n");
	var elements = new Array();

	for (let i = 0; i< lines.length; i++){
		elements[i] = lines[i];
	}

	var numbers = new Array();
	var elementsFinal = Create2DArray(elements.length);

	for (let i = 0; i<elements.length;i++){
		numbers[i] = lines[i].split(" ");
		var temporary = numbers[i];
		for (let j = 0; j<numbers[i].length;j++){
			elementsFinal[i][j] = parseInt(temporary[j]);
		}
	}
	return elementsFinal;
}

function Create2DArray(rows) {
  var arr = [];

  for (var i=0;i<rows;i++) {
     arr[i] = [];
  }

  return arr;
}

function getText(filename){
    var rawFile = new XMLHttpRequest();
    rawFile.open("GET", filename, false);
    var allText;
    rawFile.onreadystatechange = function ()
    {
        if(rawFile.readyState === 4)
        {
            if(rawFile.status === 200 || rawFile.status == 0)
            {
                allText = rawFile.responseText;
            }
        }
    }
    rawFile.send(null);
    return allText;
}

function showPauseMenu(buttons){
	buttons[0].style.visibility = 'visible';
	buttons[1].style.visibility = 'visible';
	buttons[2].style.visibility = 'visible';
}

function unshowPauseMenu(buttons){
	buttons[0].style.visibility = 'hidden';
	buttons[1].style.visibility = 'hidden';
	buttons[2].style.visibility = 'hidden';
}

function showGameOverMenu(buttons){
	buttons[3].style.visibility = 'visible';
	buttons[4].style.visibility = 'visible';
	buttons[5].style.visibility = 'visible';
}

function unShowGameOverMenu(buttons){
	buttons[3].style.visibility = 'hidden';
	buttons[4].style.visibility = 'hidden';
	buttons[5].style.visibility = 'hidden';
}

function animation(i, reqID,player, levels,buttons){
	reqID = window.requestAnimationFrame(function(){
		animation(i, reqID,player, levels,buttons);
	});
	if(!levels[i].endLevel){
		if(!levels[i].pause.pause){
			levels[i].refreshFrame();

			//Make sure that menu pause isn't being showed
			//when it's not supposed to
			if(!levels[i].pause2.pause2){
				if(buttons[0].style.visibility == 'visible'){
				unshowPauseMenu(buttons);
				}
			}
			//Make sure that game over menu isn't being showed
			//when it's not supposed to
			if(!levels[i].pause3.pause3){
				if(buttons[3].style.visibility == 'visible'){
				unShowGameOverMenu(buttons);
				}
			}
		}
		if(levels[i].pause2.pause2){
			showPauseMenu(buttons);
		}
		if(levels[i].pause3.pause3){
			showGameOverMenu(buttons);
		}
	}
	else if(levels[i].endLevel){
		player.coins+=levels[i].ttlCoins;
		player.finalPoints+=levels[i].points;
		levels[i].ttlCoins = 0;
		levels[i].points = 0;
		levels[i].music.pause();
		i++;
		if(i==5){
				console.log("ENd of level 5");
				window.parent.postMessage(
            	{
                	state: "endlevels",
            	}, '*');
			}
		if(i < levels.length-1){
			
			alert("Current level: " + i);
			
			levels[i].music.play();
		}
		if(i<levels.length){
			levels[i].buggy.lives = levels[i-1].buggy.lives;
			levels[i].ttlCoins = player.coins;
			levels[i].points = player.finalPoints;
			console.log(player.name + " /Points: " + player.finalPoints + " /"  +i);

			//Update dos dados do player
			var text;// = getCookie("currentPlayer");
			//var info = text.split("/");
			text = "exist" + "/" + player.name + "/" + player.age + "/"+player.finalPoints + "/" + (player.lastLevel+1);

			setCookie("currentPlayer",text,10);
			
			window.parent.postMessage(
	            {
	                state: "updateData",
	                player: {
	                    name: player.name,
	                    score: player.finalPoints,
	                    lastLevel: i,
	                }
	            }, '*');
		}
		
	}
	if(i<levels.length){
		if(levels[i].buggy.lives <= 0){
			if(i!=0){levels[i].music.pause();}
			
			i = 0;
			levels[i].music.play();
			//player.coins = 0;
			for (var j = 0; j<levels.length; j++) {
				levels[j].loadLevel(levels[j].map,levels[j].music,levels[j].coinSound);
				levels[j].endLevel = false;
			}
			window.parent.postMessage(
	            {
	                state: "updateData",
	                player: {
	                    name: player.name,
	                    score: player.finalPoints,
	                    lastLevel: "0",
	                    repeat: "true",
	                }
	            }, '*');
			var text = "exist" + "/" + player.name + "/" + player.age + "/"+player.finalPoints + "/" + "0";

			setCookie("currentPlayer",text,10);
			//Remove points to player when it loses?
			//Identical call
		}
	} 

	if(i==levels.length){
			console.log("No more frames required!");
			window.cancelAnimationFrame(reqID);
	}
}

class Level{
	constructor(ctx, canvas, tileSrc, type){
		this.background = new Image();
		this.background.src = tileSrc;

		this.ctx = ctx;
		this.c = canvas;
		this.moneyBags = [];
		this.ttlCoins = 0;
		this.points = 0;
		this.endFlag = null;
		this.endLevel = false;									// Caso seja true, passa para o prox nivel	//
		this.buggy = null;										//variavel iniciada a null com  			//
																//fins de controlo de erros					//
		this.pause = {pause:false};
		this.pause2 = {pause2:false};
		this.pause3 = {pause3:false};
																// Verifica em que nivel e que o player esta//
		if(type == 4){
			this.type = 1.7;
		}else if(type == 5){
			this.type = 2;
		}else{this.type = 1;}
	}
	
	loadLevel(map,music,coinSound){

		this.map = map;

		this.sprites = [];
		this.boxes = [];
		this.enemies = [];
		this.coins = [];
		this.bateries = [];
		this.sboxes = [];
		this.lasers=[];
		this.visiLasers = 1;
		this.boss = [];
		this.music = music;
		this.coinSound = coinSound;
		//console.log(this.coinSound);

		var EMPTY = 0;											// Variaveis usadas para dar load ao mapa	//
		var BOX = 1;											// Cada uma delas tem o seu valor respetivo	//
		var BUGGY = 2;											// no array     							//
		var ENEMY = 3;
		var SBOX = 4;											
		var COIN = 5;
		var BAG = 6;
		var FLAG = 7;
		var LASER = 8;
		var BATERY = 9;
		var FINAL = 10;

		var SIZE = 50;

		this.mapHeight = this.map.length * 50;
		this.mapWidth = this.map[0].length * 50;

		var tileSheet = new Element(250, 0, this.mapWidth, this.mapHeight, this.mapWidth, this.mapHeight, 0, 0);
		this.sprites.push(tileSheet);

		for(let l = 0; l < this.map.length; l++){
			for(let col = 0; col < this.map[l].length; col++){
				let curr = this.map[l][col];
				if(curr != EMPTY){
					switch(curr){
						case BUGGY:
							this.buggy = new Buggy(10, 0, 50, 102, 50, 100, col*SIZE, l*SIZE);
							this.sprites.push(this.buggy);
							break;
						case BOX:
							var box = new Element(10, 412, 47, 47, 50, 50, col*SIZE, l*SIZE);
							this.sprites.push(box);
							this.boxes.push(box);
							break;
						case COIN:
							var coin = new Element(10, 462, 50, 50, 50, 50, col*SIZE, l*SIZE);
							this.sprites.push(coin);
							this.coins.push(coin);
							break;
						case FLAG:
							this.endFlag = new Element(95, 410, 32, 54, 50, 50, col*SIZE, l*SIZE);
							this.sprites.push(this.endFlag);
							break;
						case ENEMY:
							var enemy = new Enemy(72, 338, 158, 72, 50, 50, col*SIZE, l*SIZE);
							this.sprites.push(enemy);
							this.enemies.push(enemy);
							break;
						case LASER:
							var laser = new Element(229, 9, 6, 267, 7, 600, col*SIZE, l*SIZE);
							if(this.type == 2){laser.final = true;}
							this.sprites.push(laser);
							this.lasers.push(laser);
							break;
						case BAG:
							var bag = new Element(62, 423, 38, 50, 50, 50, col*SIZE, l*SIZE);
							this.sprites.push(bag);
							this.moneyBags.push(bag);
							break;
						case SBOX:
							var sbox = new Element(114, 71, 50, 50, 50, 50, col*SIZE, l*SIZE);
							sbox.visible = false;
							this.sprites.push(sbox);
							this.sboxes.push(sbox);
							break;
						case BATERY:
							var batery = new Element(117, 5, 50, 50, 50, 50, col*SIZE, l*SIZE);
							this.sprites.push(batery);
							this.bateries.push(batery);
							break;
						case FINAL:
							var fBoss = new FinalBoss(218, 403, 238, 182, 250, 200, col*SIZE, l*SIZE);
							this.sprites.push(fBoss);
							this.boss.push(fBoss);
							break;
						default: break;

					}
				}
			}
		}

		if(this.type == 1.7){
			this.buggy.gravity /= this.type*2.5; 					// Alteraçoes para da gravidade e do jump 	//
			this.buggy.jumpForce *= this.type/2;					// force para o nivel 4 					//
		}
	
		this.background.addEventListener("load", loadHandler);	
		this.camera = new Camera(this.c.width, this.c.height);
		
		this.loadAndStart();										// Funcao responsavel por implementar os 	//
																	// eventos que vao ler as teclas para 		//
																	// comandar o Buggy e pela a animacao toda 	//
		function loadHandler(){
			console.log("background loaded");
		}
	}
	
	loadAndStart(){
		var SPACE = 32;												// Variaveis com os valores das teclas usadas//
		var RIGHT = 39;
		var LEFT = 37;

		var buggy = this.buggy;
		var pause = this.pause;
		var pause2 = this.pause2;

		window.addEventListener("keydown", function(event){
		 switch(event.keyCode){
			case LEFT:
			 	buggy.moveLeft = true;
			 	buggy.sourceX = 10;
				buggy.sourceY = 310;
			 	break;

			case RIGHT:
			 	buggy.moveRight = true;
			 	buggy.sourceX = 10;
				buggy.sourceY = 104;
			 	break;

			case SPACE:
			 	buggy.jump = true;
			 	break;
		 	case 80:
		 		pause.pause = !pause.pause;
		 		pause2.pause2 = !pause2.pause2;
		 		break;

		 	 default: break;
			}
		}, false);

		window.addEventListener("keyup", function(event){
			switch(event.keyCode){
			case LEFT:
				buggy.moveLeft = false;
				buggy.sourceX = 9;
				buggy.sourceY = 208;
				break;

			case RIGHT:
			 	buggy.sourceX = 10;
				buggy.sourceY = 0;
				buggy.moveRight = false;
				break;
			 
			case SPACE:
			 	buggy.jump = false;
			 	break;
		 	default: break;
			}
		}, false);
	}

	refreshFrame(){
		this.moveComands();										// Funcao da atualizaçao da posicao do Buggy//
	
		//Scroll the camera
		if(this.buggy.x < this.camera.leftInnerBoundary()){
		 	this.camera.x = Math.floor(this.buggy.x - (this.camera.width * 0.5)); //0.25
		}
		if(this.buggy.y < this.camera.topInnerBoundary()){
		 	this.camera.y = Math.floor(this.buggy.y - (this.camera.height * 0.5)); //0.25
		}
		if(this.buggy.x + this.buggy.width > this.camera.rightInnerBoundary()){
		 	this.camera.x = Math.floor(this.buggy.x + this.buggy.width - (this.camera.width * 0.5)); // 0.75
		}
		if(this.buggy.y + this.buggy.height > this.camera.bottomInnerBoundary()){
		 	this.camera.y = Math.floor(this.buggy.y + this.buggy.height - (this.camera.height * 0.5)); //0.75
		}

		//The camera's world boundaries
		if(this.camera.x < 0){
		 	this.camera.x = 0;
		}
		if(this.camera.y < 0){
		 	this.camera.y = 0;
		}
		if(this.camera.x + this.camera.width > 0 + this.mapWidth){
		 	this.camera.x = 0 + this.mapWidth - this.camera.width;
		}

		if(this.camera.y + this.camera.height > this.mapHeight){
		 	this.camera.y = this.mapHeight - this.camera.height;
		}  
		this.render();		// Funcao que redesenha o nivel em cada	//
							// frame 								//
	}

	moveComands(){
		if(this.buggy.moveLeft && !this.buggy.moveRight){
		 	this.buggy.accelerationX = -0.2;
		 	this.buggy.friction = 1;
		}
		//Right
		if(this.buggy.moveRight && !this.buggy.moveLeft){
		 	this.buggy.accelerationX = 0.2;
		 	this.buggy.friction = 1; 
		}
		//Set the buggy's velocity and acceleration to zero if none of the keys are being pressed
		if(!this.buggy.moveLeft && !this.buggy.moveRight){
		 	this.buggy.accelerationX = 0;
		 	this.buggy.vx = 0;
		}
		if(this.buggy.jump && this.buggy.onGround){
			this.buggy.vy += this.buggy.jumpForce;
			this.buggy.onGround = false;
			this.buggy.friction = 1;
		}
		//Apply the acceleration
		this.buggy.vx += this.buggy.accelerationX;
		this.buggy.vy += this.buggy.accelerationY;
		//Apply friction
		this.buggy.vx *= this.buggy.friction;
		//Apply gravity
		this.buggy.vy += this.buggy.gravity; 
		//Limit the speed
		if (this.buggy.vx > this.buggy.speedLimit){
		 	this.buggy.vx = this.buggy.speedLimit;
		}
		if (this.buggy.vx < -this.buggy.speedLimit){
			this.buggy.vx = -this.buggy.speedLimit;
		}
		if (this.buggy.vy > this.buggy.speedLimit * 2){
			this.buggy.vy = this.buggy.speedLimit * 2;	
		} 
		if (this.buggy.onGround){
			this.buggy.vx *= this.buggy.friction;
		}
		//Move the buggy
		this.buggy.x += this.buggy.vx;
		this.buggy.y += this.buggy.vy;

		//Enemy Moviment

		for(let i=0; i<this.enemies.length; i++){
			for(let j=0; j<this.boxes.length; j++){
				let collision = blockRectangle(this.enemies[i], this.boxes[j], false, true);
				
				if(collision == "right" || collision == "left"){
					this.enemies[i].vx *= -1;
				}
			}
			this.enemies[i].corner(this.boxes);
			this.enemies[i].move();
		}
		//Final Boss Moviment
		for(let i=0; i<this.boss.length; i++){
			for(let j=0; j<this.boxes.length; j++){
				let collision = blockRectangle(this.boss[i], this.boxes[j], false, true);
				
				if(collision == "right" || collision == "left"){
					this.boss[i].vx *= -1;
				}
			}
			this.boss[i].corner(this.boxes);
			this.boss[i].move();
		}

		//Screen boundaries
		if (this.buggy.x < 0){
		 	this.buggy.vx *= this.buggy.bounce;
		 	this.buggy.x = 0;
		}
		if (this.buggy.y < 0){
		 	this.buggy.vy *= this.buggy.bounce; 
		 	this.buggy.y = 0;
		}
		if (this.buggy.x + this.buggy.width > this.mapWidth){
		 	this.buggy.vx *= this.buggy.bounce;
		 	this.buggy.x = this.mapWidth - this.buggy.width;
		}
		if (this.buggy.y + this.buggy.height > this.mapHeight){ //aqui vai retirar vidas para qd o buggy bate no fundo do mapa
		 	this.buggy.vy = -this.buggy.gravity; 
		 	this.buggy.onGround = true;
		 	this.buggy.y = this.mapHeight - this.buggy.height;
		 	this.loseLife();
		}

		//Colisoes
		//Caixas/ Plataformas
		for(let i = 0; i < this.boxes.length; i++){
		 	
		 	var collisionSide = blockRectangle(this.buggy, this.boxes[i], false, true);

			if(collisionSide === "bottom" && this.buggy.vy >= 0){
			 	//Tell the game that the buggy is on the ground if it's standing on top of a platform
			 	this.buggy.onGround = true;
			 	//Neutralize gravity by applying its exact opposite force to the character's vy
			 	this.buggy.vy = -this.buggy.gravity;
			}
			else if(collisionSide === "top" && this.buggy.vy <= 0){
			 	this.buggy.vy = 0;
			 	if(this.type == 1.7){
					this.loseLife();
				}
			}
			else if(collisionSide === "right" && this.buggy.vx >= 0){
			 	this.buggy.vx = 0;
			}
			else if(collisionSide === "left" && this.buggy.vx <= 0){
			 	this.buggy.vx = 0;
			}			
			if(collisionSide !== "bottom" && this.buggy.vy > 0){
			 	this.buggy.onGround = false;
			}
		}
		//Enimigos
		for(let i = 0; i<this.enemies.length; i++){
			let collision = blockRectangle(this.buggy, this.enemies[i], true, true);
			if(collision!= "none"){
				this.loseLife();			
			}
		}
		for(let i = 0; i<this.boss.length; i++){
			let collision = blockRectangle(this.buggy, this.boss[i], true, true);
			if(collision!= "none" && collision!="bottom" && this.boss[i].lives > 0){
				this.buggy.vx=0;
				this.buggy.vy=0;
				this.loseLife();			
			}else if(collision == "bottom" && this.boss[i].lives > 0){
				this.hitBoss(this.boss[i]);
			}
		}
		//Lasers
		for(let i = 0; i<this.lasers.length; i++){
			let collision = blockRectangle(this.buggy, this.lasers[i], false, false);
			if(collision!= "none" && this.lasers[i].visible){
				this.loseLife();			
			}
			if(!this.lasers[i].final){
				if(this.visiLasers%75 == 0){
					this.lasers[i].visible = !this.lasers[i].visible;
					this.visiLasers = 1;
				}else{
					this.visiLasers++;
					//console.log(this.visiLasers);
				}
			}else{
				for(let j=0; j<this.boss.length; j++){
					if(this.boss[j].lives == 0){
						this.lasers[i].visible = false;
					}else{
						this.lasers[i].visible = true;
					}
				}
			}
		}
		//Moedas
		for(let i = 0; i < this.coins.length; i++){
			if(this.coins[i].visible){
				let collision = blockRectangle(this.buggy, this.coins[i], false, false);
				if(collision != "none"){
					this.coins[i].visible = false;
					this.ttlCoins++;
					this.points+=2;
				}
			}
		}
		for(let i = 0; i < this.moneyBags.length; i++){
			if(this.moneyBags[i].visible){
				let collision = blockRectangle(this.buggy, this.moneyBags[i], false, false);
				if(collision != "none"){
					this.moneyBags[i].visible = false;
					this.ttlCoins+=5;
					this.points+=10;
				}
			}
		}	
		//Colisao com plataformas supresa
		for(let i = 0; i < this.sboxes.length; i++){
			let collision = blockRectangle(this.buggy, this.sboxes[i], false, false);

			if(!this.sboxes[i].visible){
				if(collision === "top" && this.buggy.vy <= 0){
					this.buggy.vy = 0;
					this.sboxes[i].visible = true;
					this.ttlCoins+=2;
					this.points+=2;
				}
			}
			else{
				if(collision === "bottom" && this.buggy.vy >= 0){
			 		this.buggy.onGround = true;
			 		this.buggy.vy = -this.buggy.gravity;
				}
				if(collision === "top" && this.buggy.vy <= 0){
				 	this.buggy.vy = 0;
				}
				if(collision === "right" && this.buggy.vx >= 0){
				 	this.buggy.vx = 0;
				}
				if(collision === "left" && this.buggy.vx <= 0){
				 	this.buggy.vx = 0;
				}			
				if(collision  !== "bottom" && this.buggy.vy > 0){
				 	this.buggy.onGround = false;
				}
			}
		}			
		//Flag
		if(this.endFlag != null){
			let collision = blockRectangle(this.buggy, this.endFlag, false, false);
			if(collision!="none"){
				this.endLevel = true;
			}
		}

		for(let i = 0; i < this.bateries.length; i++){
			if(this.bateries[i].visible){
				let collision = blockRectangle(this.buggy, this.bateries[i], false, false);
				if(collision != "none"){
					this.bateries[i].visible = false;
					if(this.buggy.lives < 4){
						this.buggy.lives+=1;
					}
				}
			}
		}

		function blockRectangle(r1, r2, bounce, blocked){
			//Set bounce to a default value of false if it's not specified
			 if(typeof bounce === "undefined"){
			 	bounce = false;
			 }

			 //A variable to tell us which side the collision is occurring on
			 var collisionSide = "";
			 
			 //Calculate the distance vector
			 var vx = r1.centerX() - r2.centerX();
			 var vy = r1.centerY() - r2.centerY();

			 //Figure out the combined half-widths and half-heights
			 var combinedHalfWidths = r1.halfWidth() + r2.halfWidth();
			 var combinedHalfHeights = r1.halfHeight() + r2.halfHeight();

			 //Check whether vx is less than the combined half widths
			 if(Math.abs(vx) < combinedHalfWidths){
				 //A collision might be occurring!
				 //Check whether vy is less than the combined half heights
				if(Math.abs(vy) < combinedHalfHeights){
				 //A collision has occurred! This is good!
					 //Find out the size of the overlap on both the X and Y axes
					var overlapX = combinedHalfWidths - Math.abs(vx);
					var overlapY = combinedHalfHeights - Math.abs(vy);

					//The collision has occurred on the axis with the
					//*smallest* amount of overlap. Let's figure out which
					//axis that is
					if(overlapX >= overlapY){
					//The collision is happening on the X axis, but on which side? vy can tell us
						if(vy > 0){
						 	collisionSide = "top";
						 	//Move the rectangle out of the collision
						 	if(blocked) r1.y = r1.y + overlapY;
						}
					 	else{
						 	collisionSide = "bottom";
						 	//Move the rectangle out of the collision
						 	if(blocked) r1.y = r1.y - overlapY;
					 	}
						//Bounce
						if(bounce){
						 	if(blocked) r1.vy *= -1;
				 		}
				 	}
			 		else{
						 //The collision is happening on the Y axis, but on which side? vx can tell us
						 if(vx > 0){
						 	collisionSide = "left";
						 	//Move the rectangle out of the collision
						 	if(blocked) r1.x = r1.x + overlapX;
						 }
						 else{
						 	collisionSide = "right";
						 	//Move the rectangle out of the collision
						 	if(blocked) r1.x = r1.x - overlapX;
						 }
						 //Bounce
						 if(bounce){
						 	if(blocked) r1.vx *= -1;
						 }
			 		}
			 	}
				else{
					//No collision
					collisionSide = "none";
				}
			}	

			else{
				//No collision
				collisionSide = "none";
			}

			return collisionSide;
		}		
	}

	render(){
		this.ctx.clearRect(0, 0, 900, 600);
		this.ctx.save();
		this.ctx.translate(-this.camera.x, -this.camera.y);
		if(this.sprites.length !== 0){
		 	for(var i = 0; i < this.sprites.length; i++){
		 		var sprite = this.sprites[i];
				if(sprite.visible){
					this.ctx.drawImage(this.background,sprite.sourceX, sprite.sourceY, sprite.sourceWidth, sprite.sourceHeight,Math.floor(sprite.x), Math.floor(sprite.y),sprite.width, sprite.height);
		 		}
		 	}
		 	switch(this.buggy.lives){	// Display das vidas do buggy 	//
		 		case 1:
					this.ctx.drawImage(this.background, 63, 6, 38, 59, this.camera.x + 840, this.camera.y + 20, 38, 59);
					break;
				case 2:
					this.ctx.drawImage(this.background, 63, 69, 38, 59, this.camera.x + 840, this.camera.y + 20, 38, 59);
					break;
				case 3:
					this.ctx.drawImage(this.background, 64, 134, 38, 59, this.camera.x + 840, this.camera.y + 20, 38, 59);
					break;
				case 4:
					this.ctx.drawImage(this.background, 64, 199, 38, 59, this.camera.x + 840, this.camera.y + 20, 38, 59);
					break;
				default: break;
		 	}

			this.ctx.font = "25px Arial";
			this.ctx.fillStyle = "#e6b800";
			this.ctx.drawImage(this.background,134,414,70,50,this.camera.x + 20, this.camera.y + 20, 70,50);
			this.ctx.fillText(this.ttlCoins, this.camera.x + 92, this.camera.y + 52);
			this.ctx.drawImage(this.background,63,268,160,70,this.camera.x + 390,this.camera.y + 12,160,70);
			this.ctx.fillText(this.points,this.camera.x + 450, this.camera.y + 52);
		 	this.ctx.restore();
		}
	}	

	loseLife(){
		this.buggy.lives -= 1;
		
		if(this.ttlCoins-20 >= 0){
			this.ttlCoins-=20;
		}else{this.ttlCoins=0;}

	 	var buggy = this.buggy;
	 	this.pause = {pause:true};
	 	this.pause3.pause3 = true;

	 	buggy.sourceX = 0;
	 	buggy.sourceY = 523;
	 	buggy.sourceWidth = 102;
	 	buggy.width = 102;
	 	buggy.y += 25;
	 	setTimeout(function(){
	 		buggy.sourceX = 10;
		 	buggy.sourceY = 0;
		 	buggy.sourceWidth = 50;
		 	buggy.sourceHeight = 102;
		 	buggy.width = 50;
		 	buggy.height = 100;
		 	this.pause = {pause:false};
		 	buggy.x = buggy.respawnX;
	 		buggy.y = buggy.respawnY;
	 	}, 750);	
	}

	hitBoss(boss){
		boss.lives--;
		if(boss.lives>6){
			boss.vx*=-4;
			setTimeout(function(){
		 		boss.vx/=-4;
		 	}, 450);
		}else if(boss.lives == 6){
			boss.vx *= 3;
			boss.sourceX = 234;
		 	boss.sourceY = 210;
		}else if(boss.lives == 3){
			boss.vx*=2;
			boss.sourceX = 234;
		 	boss.sourceY = 11;
		}else if(boss.lives<=0){
			this.visiLasers = 0;
			boss.vx = 0;
		}	
	}                                     
}

class Camera{
	constructor(w, h){
		this.x = 0;
		this.y = 0;
		this.width = w;
		this.height = h;
	}
	rightInnerBoundary(){
		return this.x + (this.width * 0.5); //0.75
	}

	leftInnerBoundary(){
		return this.x + (this.width * 0.5); //0.25
	}

	topInnerBoundary(){
		return this.y + (this.height * 0.5); //0.25
	}
	
	bottomInnerBoundary(){
		return this.y + (this.height * 0.5); // 0.25
	}
}

class Element{
	constructor(sx, sy, sw, sh, w, h, x, y){
		this.sourceX = sx;										// Localizacao da sprite na sprite sheet 	//
		this.sourceY = sy;
		this.sourceWidth = sw;
		this.sourceHeight = sh;
		this.width = w;
		this.height = h;
		this.x = x;
		this.y = y;
		this.visible = true;
		this.final = false;
	}
	centerX(){
	 	return this.x + (this.width / 2);
	}
	centerY(){
	 	return this.y + (this.height / 2);
	}
	halfWidth(){
	 	return this.width / 2;
	}
	halfHeight(){
	 	return this.height / 2;
	}
}

class Enemy extends Element{
	constructor(sx, sy, sw, sh, w, h, x, y){
		super(sx, sy, sw, sh, w, h, x, y);
		this.vx = 1;
		this.vy = 0;
		this.respawnX = x;
		this.respawnY = y;
		this.SIZE_X = 50;
		this.SIZE_Y = 50;
	}
	move(){
		this.x += this.vx;
		this.y += this.vy;
	}
	corner(boxes){
		if(Math.floor(this.x)%50 === 0 && Math.floor(this.y)%50 === 0){
																//Muda a direção caso haja um obstaculo ao 	//
																//lado ou nao haja um em baixo				//
																// Enconta em que linha e coluna é que o 	//
																// enimigo esta 							//
			var belowLeft = false;
			var belowRight = false;
			for(let i=0; i<boxes.length; i++){
				if(this.vx > 0){
					if((this.x+this.SIZE_X === boxes[i].x)&&(this.y+this.SIZE_Y === boxes[i].y)){
						belowRight = true;
					}
				}else if(this.vx < 0){
					if((this.x-50 === boxes[i].x)&&(this.y+this.SIZE_Y === boxes[i].y)){
						belowLeft = true;
					}
				}
			}
			if( (!belowRight && !belowLeft) ){
				this.vx *= -1;
			}
		}
	}
}

class Buggy extends Element{
	constructor(sx, sy, sw, sh, w, h, x, y){
		super(sx, sy, sw, sh, w, h, x, y);
		this.jump = false;
		this.moveRight = false;									//Estas duas variaveis servem para atrito 	//
		this.moveLeft = false;									//em caso de mudança de direçao repentina 	//
		
		this.vy = 0;
		this.vx = 0;

		//Physics Vars
		this.accelerationX = 0;
		this.accelerationY = 0;
		this.speedLimit = 5;
		this.friction = 0.96;
		this.bounce = -0.7;
		this.gravity = 0.3;

		//Plataform vars
		this.onGround = undefined;
		this.jumpForce = -10;

		this.lives = 4;
		this.respawnX = x;
		this.respawnY = y;
	}
}

class FinalBoss extends Enemy{
	constructor(sx, sy, sw, sh, w, h, x, y){
		super(sx, sy, sw, sh, w, h, x, y);
		this.vx = 2;
		this.vy = 0;
		this.SIZE_X = 250;
		this.SIZE_Y = 200;
		this.lives = 9;
	}
}

class Player{
	constructor(name, age,score,lastLevel){
		this.name = name;
		this.age = age;
		this.coins = 0;
		this.finalPoints = score;
		this.lastLevel = lastLevel;
	}
}