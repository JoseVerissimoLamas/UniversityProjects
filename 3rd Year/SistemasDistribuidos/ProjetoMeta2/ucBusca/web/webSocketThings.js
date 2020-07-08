
var websocket = null;

window.onload = function() {
    console.log("AHHHHHH");
    connect('ws://' + window.location.host + '/ucBusca/ws');
    console.log('ws://' + window.location.host + '/ucBusca/ws');
}

function connect(host) { // connect to the host websocket
    if ('WebSocket' in window)
        websocket = new WebSocket(host);
    else if ('MozWebSocket' in window)
        websocket = new MozWebSocket(host);
    else {
        return;
    }

    websocket.onopen    = onOpen;
    websocket.onclose   = onClose;
    websocket.onmessage = onMessage;
}

function onOpen(event) {
    var user = document.getElementById("username");
    console.log("alguma coisa");
    doSend();
}

function onClose(event) {
}

function doSend() {
    var user = document.getElementById("username");
    var username = user.innerText;
    websocket.send(username);
}

function onMessage(message) { // print the received message
    console.log(message);
    writeNotification();
}

function writeNotification(){
    var notification=document.createElement("not");
    notification.innerText="Congratulations you are now an admin";
    document.body.appendChild(notification);
}