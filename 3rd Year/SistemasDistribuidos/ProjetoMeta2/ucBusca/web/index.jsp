<%--
  Created by IntelliJ IDEA.
  User: Beatriz
  Date: 06/12/2019
  Time: 14:24
  To change this template use File | Settings | File Templates.
--%>
<%@ taglib prefix="s" uri="/struts-tags"%>
<%@ taglib prefix="d" uri="/struts-tags"%>
<%@ page language="java" contentType="text/html; charset=ISO-8859-1" pageEncoding="ISO-8859-1"%>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
  <meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">

  <link href="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-Vkoo8x4CGsO3+Hhxv8T/Q5PaXtkKtu6ug5TOeNV6gBiFeWPGFN9MuhOf23Q9Ifjh" crossorigin="anonymous">
  <script src="https://code.jquery.com/jquery-3.4.1.slim.min.js" integrity="sha384-J6qa4849blE2+poT4WnyKhv5vZF5SrPo0iEjwBvKU7imGFAV0wwj1yYfoRSJoZ+n" crossorigin="anonymous"></script>
  <script src="https://cdn.jsdelivr.net/npm/popper.js@1.16.0/dist/umd/popper.min.js" integrity="sha384-Q6E9RHvbIyZFJoft+2mJbHaEWldlvI9IOYy5n3zV9zzTtmI3UksdQRVvoxMfooAo" crossorigin="anonymous"></script>
  <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/js/bootstrap.min.js" integrity="sha384-wfSDF2E50Y2D1uUdj0O3uMBJnjuUD4Ih7YwaYd1iqfktj0Uod8GCExl3Og8ifwB6" crossorigin="anonymous"></script>
  <link rel="stylesheet" href="styleSheet.css">

  <title>UcBusca</title>
</head>

<script>
  console.log("farto");
  var websocket = null;
  console.log("AHHHHHH");
  connect('ws://' + window.location.host + '/ucBusca/ws');
  console.log('ws://' + window.location.host + '/ucBusca/ws');


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

  function onClose(event) {}

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
</script>
<body>

<%@include file="header.jsp"%>

<!-- Search Word -->
<form action="search" method="post" class="searchBar">
  <div class="row" style="margin-bottom: 2%;">
    <img src="./images/UC_Logo.png" alt="uc_logo" class="indexLogo">
    <h1 class="indexTitle">UcBusca</h1>
  </div>
  <div class="input-group mb-3 row">
    <input type="text"
           class="form-control"
           placeholder="Web Search"
           aria-describedby="button-addon2"
           name = "browser.query">
    <button class="btn btn-outline-secondary" type="submit" id="button-addon2">Search</button>
  </div>
</form>

</body>
</html>