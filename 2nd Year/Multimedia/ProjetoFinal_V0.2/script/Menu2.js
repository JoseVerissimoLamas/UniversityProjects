"use strict";

(function()
{
    window.addEventListener("load", main);
}());


function main(){

    var canvas = document.getElementById("canvas");
    var ctx = canvas.getContext("2d");

    //All buttons Array
    var buttons = new Array();

    //Load Media
    var pagInicial = new Image();
    pagInicial.src = 'Menu/background.png'
    pagInicial.style.backgroundSize = 'cover';
    pagInicial.style.backgroundRepeat = 'no-repeat';

    var menu = new Image();
    menu.src = 'Menu/menu.png';
    menu.style.backgroundSize = 'cover';
    menu.style.backgroundRepeat = 'no-repeat';

    var cred = new Image();
    cred.src = 'Menu/creditos_jogo.png';
    cred.style.backgroundSize = 'cover';
    cred.style.backgroundRepeat = 'no-repeat';

    var ajuda = new Image();
    ajuda.src = 'Menu/ajuda_jogo1.png';
    ajuda.style.backgroundSize = 'cover';
    ajuda.style.backgroundRepeat = 'no-repeat';

    var opcoes = new Image();
    opcoes.src = 'Menu/opcoes_jogo.png';
    opcoes.style.backgroundSize = 'cover';
    opcoes.style.backgroundRepeat = 'no-repeat';

    var ranking = new Image();
    ranking.src = 'Menu/ranking_jogo.png';
    ranking.style.backgroundSize = 'cover';
    ranking.style.backgroundRepeat = 'no-repeat';

    var jogo = new Image();
    jogo.src = 'Menu/novo_jogo.png';
    jogo.style.backgroundSize = 'cover';
    jogo.style.backgroundRepeat = 'no-repeat';


    pagInicial.addEventListener("load",loadPagInicial);

    //Initial Button
    var continuarBttn = document.getElementById('continuar');
    buttons.push(continuarBttn);

    //Menu Contents
    var jogarBttn = document.getElementById('jogar');
    buttons.push(jogarBttn);
    var rankingBttn = document.getElementById('ranking');
    buttons.push(rankingBttn);
    var opcoesBttn = document.getElementById('opcoes');
    buttons.push(opcoesBttn);
    var ajudaBttn = document.getElementById('ajuda');
    buttons.push(ajudaBttn);
    var creditosBttn = document.getElementById('creditos');
    buttons.push(creditosBttn);
    var sairBttn = document.getElementById('sair');
    buttons.push(sairBttn);

    //Voltar Option
    var voltarBttn = document.getElementById('voltar');
    buttons.push(voltarBttn);

    //Jogar Contents
    var inputName = document.getElementById('inputName');
    buttons.push(inputName);
    var inputAge = document.getElementById('inputAge');
    buttons.push(inputAge);
    var newGame = document.getElementById('NewGame');
    buttons.push(newGame);
    var confirmNewGameBox = document.getElementById('NewGameBox');
    buttons.push(confirmNewGameBox);
    var simNewGameBttn = document.getElementById('simNewGameBttn');
    buttons.push(simNewGameBttn);
    var naoNewGameBttn = document.getElementById('naoNewGameBttn');
    buttons.push(naoNewGameBttn);
    
    //Sair Content
    var simBttn = document.getElementById('sim');
    buttons.push(simBttn);
    var naoBttn = document.getElementById('nao');
    buttons.push(naoBttn);
    var confirm_box = document.getElementById('confirmBox');
    buttons.push(confirm_box);

    //Options Content
    var maisvolume = document.getElementById('maisvolume');
    buttons.push(maisvolume);
    var menosvolume = document.getElementById('menosvolume');
    buttons.push(menosvolume);
    var com_som = document.getElementById('com_som');
    buttons.push(com_som);
    var sem_som = document.getElementById('sem_som');
    buttons.push(sem_som);
    var maisvolume2 = document.getElementById('maisvolume2');
    buttons.push(maisvolume2);
    var menosvolume2 = document.getElementById('menosvolume2');
    buttons.push(menosvolume2);
    var com_som2 = document.getElementById('com_som2');
    buttons.push(com_som2);
    var sem_som2 = document.getElementById('sem_som2');
    buttons.push(sem_som2);
    var com_som_2 = document.getElementById('com_som_2');
    buttons.push(com_som_2);
    var com_som_1 = document.getElementById('com_som_1');
    buttons.push(com_som_1);
    var com_som_22 = document.getElementById('com_som_22');
    buttons.push(com_som_22);
    var com_som_11 = document.getElementById('com_som_11');
    buttons.push(com_som_11);

    //Ranking
    var rankingTable = document.getElementById('highScores');
    rankingTable.style.visibility = 'hidden';
    rankingTable.style.borderSpacing = "50px";

    //Audio Content
    var mouse_sound = document.getElementById('mouse_click');
    var gameMusic = new Audio("track.mp3");

    if(getCookie("SoundVolume")!=""){
        var text = getCookie("SoundVolume");
        var sound = parseFloat(text);
        mouse_sound.volume = sound;
        text = getCookie("MusicVolume");
        sound = parseFloat(text);
        gameMusic.volume = sound;
    }
    else{
        mouse_sound.volume = 1;
        gameMusic.volume = 1;
    }
    

    var volumeMusicBttn = 3;
    var volumeSoundsBttn = 3;

    //Hide all the buttons
    hideAllButtons(buttons);

    jogarBttn.addEventListener("click",jogoHandler);
    rankingBttn.addEventListener("click",rankingHandler);
    opcoesBttn.addEventListener("click",opcoesHandler);
    ajudaBttn.addEventListener("click",ajudaHandler);
    creditosBttn.addEventListener("click",creditosHandler);
    sairBttn.addEventListener("click",sairHandler);
    continuarBttn.addEventListener("click",continuarHandler);
    simBttn.addEventListener("click",simHandler);
    naoBttn.addEventListener("click",naoHandler);

    maisvolume.addEventListener("click",maisVolumeHandlerMusica);
    menosvolume.addEventListener("click",menosVolumeHandlerMusica);
    maisvolume2.addEventListener("click",maisVolumeHandlerSom);
    menosvolume2.addEventListener("click",menosVolumeHandlerSom);

    newGame.addEventListener("click",newGameHandler);
    simNewGameBttn.addEventListener("click",simGameHandler);
    naoNewGameBttn.addEventListener("click",naoGameHandler);

    function loadPagInicial(){
        continuarBttn.style.visibility='visible';
        ctx.drawImage(pagInicial,0,0,pagInicial.width,pagInicial.height,0,0,canvas.width,canvas.height);
    }

    function loadMenu(){
        ctx.drawImage(menu, 0,0,menu.width,menu.height,0,0,canvas.width,canvas.height);  
    }

    function loadCreditos(){
        ctx.drawImage(cred, 0,0,cred.width,cred.height,0,0,canvas.width,canvas.height);  
    }

    function loadAjuda(){
        ctx.drawImage(ajuda, 0,0,ajuda.width,ajuda.height,0,0,canvas.width,canvas.height);  
    }

    function loadopcoes(){
        ctx.drawImage(opcoes, 0,0,opcoes.width,opcoes.height,0,0,canvas.width,canvas.height);  
    }

    function loadranking(){
        ctx.drawImage(ranking, 0,0,ranking.width,ranking.height,0,0,canvas.width,canvas.height);  
    }

    function loadjogo(){
        ctx.drawImage(jogo, 0,0,jogo.width,jogo.height,0,0,canvas.width,canvas.height);  
    }

    function clearpage(){
        ctx.clearRect(0,0,canvas.width,canvas.height);
        jogarBttn.style.visibility = 'hidden';
        creditosBttn.style.visibility = 'hidden';
        rankingBttn.style.visibility = 'hidden';
        opcoesBttn.style.visibility = 'hidden';
        ajudaBttn.style.visibility = 'hidden';
        creditosBttn.style.visibility = 'hidden';
        sairBttn.style.visibility = 'hidden';
        voltarBttn.style.visibility = 'hidden';
        maisvolume.style.visibility = 'hidden';
        menosvolume.style.visibility = 'hidden';
        com_som.style.visibility ='hidden';
        maisvolume2.style.visibility = 'hidden';
        menosvolume2.style.visibility = 'hidden';
        com_som2.style.visibility ='hidden';
    }

    function clearpagInicial(){
        ctx.clearRect(0,0,canvas.width,canvas.height);
        continuarBttn.style.visibility = 'hidden';
    }

    function drawpage(){
        loadMenu();
        jogarBttn.style.visibility = 'visible';
        creditosBttn.style.visibility = 'visible';
        rankingBttn.style.visibility = 'visible';
        opcoesBttn.style.visibility = 'visible';
        ajudaBttn.style.visibility = 'visible';
        creditosBttn.style.visibility = 'visible';
        sairBttn.style.visibility = 'visible';
    }

    function drawpageInicial(){
        loadPagInicial();
        continuarBttn.style.visibility = 'visible';
        continuarBttn.addEventListener("click",continuarHandler);
        menu.addEventListener("load",loadMenu);
    }

    function continuarHandler(){
        mouse_sound.play();
        //gameMusic.play();
        clearpagInicial();
        drawpage();
    }

    function voltarHandler(){
        mouse_sound.play();
        ctx.clearRect(0,0,canvas.width,canvas.height);
        hideAllButtons(buttons);
        rankingTable.style.visibility = 'hidden';

        drawpage();
    }

    function creditosHandler(){
        mouse_sound.play();
        clearpage();
        loadCreditos();
        voltarBttn.style.visibility = 'visible';
        voltarBttn.addEventListener("click",voltarHandler); 
    }

    function ajudaHandler(){
        mouse_sound.play();
        clearpage();
        loadAjuda();
        voltarBttn.style.visibility = 'visible';
        voltarBttn.addEventListener("click",voltarHandler);   
    }

    function menosVolumeHandlerMusica(){
        if(volumeMusicBttn>0){
            console.log("if de controlo menos musica")
            volumeMusicBttn-=1;
            console.log("Volume menos musica: " + volumeMusicBttn);
        }
        console.log("Initial volume: " + gameMusic.volume)
        if(volumeMusicBttn == 2){
            com_som.style.visibility ='hidden';
            com_som_2.style.visibility = 'visible';
            gameMusic.volume = 0.66;
            var text = "" + 0.66;
            setCookie("MusicVolume",text,10);
        }
        else if(volumeMusicBttn == 1){
            com_som_2.style.visibility = 'hidden';
            com_som_1.style.visibility = 'visible';
            gameMusic.volume = 0.33;
            var text = "" + 0.33;
            setCookie("MusicVolume",text,10);
        }
        else if(volumeMusicBttn == 0){
            com_som_1.style.visibility = 'hidden';
            sem_som.style.visibility = 'visible';
            gameMusic.volume = 0;
            var text = "" + 0;
            setCookie("MusicVolume",text,10);
            alert('Música Desligada!');
            //som.volume = 0;
        }
        console.log("Music volume: " + gameMusic.volume + "\n");
     }
    function maisVolumeHandlerMusica(){
        if(volumeMusicBttn<3){
            console.log("if de controlo mais musica");
            volumeMusicBttn+=1;
        }
        console.log("Volume: " + gameMusic.volume);
        if(volumeMusicBttn == 1){
            sem_som.style.visibility = 'hidden';
            com_som_1.style.visibility = 'visible';
            gameMusic.volume = 0.33;
            var text = "" + 0.33;
            setCookie("MusicVolume",text,10);
        }
        else if(volumeMusicBttn == 2){
            com_som_1.style.visibility = 'hidden';
            com_som_2.style.visibility = 'visible';
            gameMusic.volume = 0.66;
            var text = "" + 0.66;
            setCookie("MusicVolume",text,10);
        }
        if(volumeMusicBttn == 3){
            com_som_2.style.visibility = 'hidden';
            com_som.style.visibility = 'visible';
            gameMusic.volume = 1;
            var text = "" + 1;
            setCookie("MusicVolume",text,10);
            alert('Música no Máximo!');
        }
        console.log("Final sound: " + gameMusic.volume + "\n");
     }

    function maisVolumeHandlerSom(){
        console.log("mais volume handler som");
        console.log("Initial sound: " + mouse_sound.volume);
        if(volumeSoundsBttn<3){
            console.log("if de controlo de som");
            volumeSoundsBttn+=1;
        }
        console.log("Volume: " + volumeSoundsBttn);
        if(volumeSoundsBttn == 1){
            sem_som2.style.visibility = 'hidden';
            com_som_11.style.visibility = 'visible';
            mouse_sound.volume = 0.33;
            var text = "" + 0.33;
            setCookie("SoundVolume",text,10);
        }
        if(volumeSoundsBttn == 2){
            com_som_11.style.visibility = 'hidden';
            com_som_22.style.visibility = 'visible';
            mouse_sound.volume = 0.66;
            var text = "" + 0.66;
            setCookie("SoundVolume",text,10);
        }
        if(volumeSoundsBttn == 3){
            com_som_22.style.visibility = 'hidden';
            com_som2.style.visibility = 'visible';
            mouse_sound.volume = 1;
            var text = "" + 1;
            setCookie("SoundVolume",text,10);
            alert('Volume de sons no Máximo!');
        }
        console.log("Volume sons: " + volumeSoundsBttn +"\n");
    }
    function menosVolumeHandlerSom(){
        if(volumeSoundsBttn>0){
            volumeSoundsBttn-=1;
        }
        console.log("Volume sounds bttn: " + volumeSoundsBttn);
        if(volumeSoundsBttn == 2){
            com_som2.style.visibility ='hidden';
            com_som_22.style.visibility = 'visible';
            mouse_sound.volume = 0.66;
            var text = "" + 0.66;
            setCookie("SoundVolume",text,10);
        }
        else if(volumeSoundsBttn == 1){
            com_som_22.style.visibility = 'hidden';
            com_som_11.style.visibility = 'visible';
            mouse_sound.volume = 0.33;
            var text = "" + 0.33;
            setCookie("SoundVolume",text,10);
        }
        if(volumeSoundsBttn == 0){
            com_som_11.style.visibility = 'hidden';
            sem_som2.style.visibility = 'visible';
            mouse_sound.volume = 0;
            var text = "" + 0;
            setCookie("SoundVolume",text,10);
            alert('Sons desligados!');
        }
        console.log("\n");
    }

    

     //FAZER SONS 
    function opcoesHandler(){
        mouse_sound.play();
        clearpage();
        loadopcoes();
        voltarBttn.style.visibility = 'visible';
        voltarBttn.addEventListener("click",voltarHandler)

        
        //Visibilidade dos botões
        maisvolume.style.visibility = 'visible';
        menosvolume.style.visibility = 'visible';
        
        switch(gameMusic.volume){
            case 0:
                sem_som.style.visibility = 'visible';
                break;
            case 0.33:
                com_som_1.style.visibility = 'visible';
                break;
            case 0.66:
                com_som_2.style.visibility = 'visible';
                break;
            case 1:
                com_som.style.visibility = 'visible';
                break;
            default:
                break;
        }

        switch(mouse_sound.volume){
            case 0:
                sem_som2.style.visibility = 'visible';
                break;
            case 0.33:
                com_som_11.style.visibility = 'visible';
                break;
            case 0.66:
                com_som_22.style.visibility = 'visible';
                break;
            case 1:
                console.log("Did you pass trough here?");
                com_som2.style.visibility = 'visible';
                break;
            default: 
                break;
        }

        maisvolume2.style.visibility = 'visible';
        menosvolume2.style.visibility = 'visible';
    }

     //FAZER CAIXA DE TEXTO PARA PONTUAÇOES 
    function rankingHandler(){
        mouse_sound.play();
        clearpage();
        loadranking();
        voltarBttn.style.visibility = 'visible';
        rankingTable.style.visibility = 'visible';

        window.parent.postMessage(
            {
                state: "orderPlayers",
            },'*');

        var text = getCookie("allPlayers");
        var lines = text.split("*");
        console.log("Order players");
        for (let i = 0; i <= lines.length-2; i++) {
            console.log("Current line: " + lines[i]);
            var [name,age,score] = lines[i].split('/');
            console.log(name + "|" + age + "|" + score+"\n");
            
            //Write to table
            var nameId = "Name"+(i+1);
            var scoreId = "Score"+(i+1);
            document.getElementById(nameId).innerHTML = name;
            document.getElementById(scoreId).innerHTML = score;
        }


        console.log("Supostamente vemos a tabela");
        voltarBttn.addEventListener("click",voltarHandler);   
     }

    function jogoHandler(){
        mouse_sound.play();
        clearpage();
        loadjogo();
        voltarBttn.style.visibility = 'visible';
        newGame.style.visibility = 'visible';
        inputAge.style.visibility = 'visible';
        inputName.style.visibility = 'visible';
        voltarBttn.addEventListener("click",voltarHandler);   
     }
    function simHandler(){
        mouse_sound.play();
        window.close();
     }
    function naoHandler(){
        mouse_sound.play();
        naoBttn.style.visibility = 'hidden';
        simBttn.style.visibility = 'hidden';
        confirm_box.style.visibility ='hidden';
        drawpage();
     }

    function sairHandler(){
        mouse_sound.play();
        confirm_box.style.visibility ='visible';
        naoBttn.style.visibility = 'visible';
        simBttn.style.visibility = 'visible';
        jogarBttn.style.visibility = 'hidden';
        creditosBttn.style.visibility = 'hidden';
        rankingBttn.style.visibility = 'hidden';
        opcoesBttn.style.visibility = 'hidden';
        ajudaBttn.style.visibility = 'hidden';
        creditosBttn.style.visibility = 'hidden';
        sairBttn.style.visibility = 'hidden';
        maisvolume.style.visibility = 'hidden';
        menosvolume.style.visibility = 'hidden';
        com_som.style.visibility ='hidden';
        maisvolume2.style.visibility = 'hidden';
        menosvolume2.style.visibility = 'hidden';
        com_som2.style.visibility ='hidden';
     }

    function newGameHandler(){
        var name = inputName.value;
        var flag = true;
        if(name==""){flag = false;alert("O nome tem de ter pelo menos uma letra");}
        
        var age = parseInt(inputAge.value);

        if(isNaN(age)){flag = false;alert("A idade tem de ser um numero!");}
        

        if(flag){
            window.parent.postMessage(
            {
                state: "endmenu",
                player: {
                    name: name,
                    age: age
                }
            }, '*');
            console.log("fim do suposto menu");

            var control = getCookie("answerPlayer");
            if(control != ""){
                setCookie("answerPlayer","",10);
            }

            setTimeout(function(){}, 5);
            console.log("Gdhcjjkcn");

            var answer = getCookie("currentPlayer");
            var info = answer.split("/");
            console.log("Resposta recebida: " + answer + "|" + info[0]);
            //Display verification dialog
            if(info[0] === "exist"){
                newGame.style.visibility='hidden';
                inputName.style.visibility='hidden';
                inputAge.style.visibility='hidden';
                simNewGameBttn.style.visibility = 'visible';
                naoNewGameBttn.style.visibility = 'visible';
                confirmNewGameBox.style.visibility = 'visible';
            }
        }
    }
    function naoGameHandler(){
        window.parent.postMessage({state: "decision",decision:"no",}, '*');
        alert("Recomeçarás o jogo do inicio");
    }

    function simGameHandler(){
        window.parent.postMessage({state: "decision",decision:"yes",}, '*');
        alert("Estamos a recuperar o seu progresso...");
    }


    //Set Cookie Sounds
    var text = "" + 1;
    if(getCookie("SoundVolume")==""){
        setCookie("SoundVolume",text,10);
        setCookie("MusicVolume",text,10);
    }
}

function hideAllButtons(buttons){
    for (var i = 0; i <= buttons.length - 1; i++) {
        buttons[i].style.visibility='hidden';
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
            //console.log("Devolvido: " + c.substring(name.length, c.length));
            return c.substring(name.length, c.length);
        }
    }
    return "";
    
}
function setCookie(cname,cvalue,exdays){
    var d = new Date();
    d.setTime(d.getTime() + (exdays * 24 * 60 * 60 * 1000));
    var expires = "expires"+d.toUTCString();
    document.cookie = cname + "=" + cvalue + ";" + expires + ";path=/";
}
