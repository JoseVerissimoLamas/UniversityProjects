<%--
  Created by IntelliJ IDEA.
  User: Zé VL
  Date: 06/12/2019
  Time: 17:23
  To change this template use File | Settings | File Templates.
--%>
<%@ taglib prefix="d" uri="/struts-tags"%>
<%@ taglib prefix="s" uri="/struts-tags"%>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core"%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <link href="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-Vkoo8x4CGsO3+Hhxv8T/Q5PaXtkKtu6ug5TOeNV6gBiFeWPGFN9MuhOf23Q9Ifjh" crossorigin="anonymous">
    <script src="https://code.jquery.com/jquery-3.4.1.slim.min.js" integrity="sha384-J6qa4849blE2+poT4WnyKhv5vZF5SrPo0iEjwBvKU7imGFAV0wwj1yYfoRSJoZ+n" crossorigin="anonymous"></script>
    <script src="https://cdn.jsdelivr.net/npm/popper.js@1.16.0/dist/umd/popper.min.js" integrity="sha384-Q6E9RHvbIyZFJoft+2mJbHaEWldlvI9IOYy5n3zV9zzTtmI3UksdQRVvoxMfooAo" crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/js/bootstrap.min.js" integrity="sha384-wfSDF2E50Y2D1uUdj0O3uMBJnjuUD4Ih7YwaYd1iqfktj0Uod8GCExl3Og8ifwB6" crossorigin="anonymous"></script>
    <link rel="stylesheet" href="styleSheet.css">

    <title>UcBusca Results</title>
</head>
<body>
    <%@include file="header.jsp"%>
    <s:form id="form" action="remoteAction" method="post">
        <s:textfield type="hidden" id="remote" value=""></s:textfield>
    </s:form>
</body>
<script>
    var loca = window.location.search;
    if(loca.includes("fbclid") === true) {
        var string = loca.split("&")
        var term = string[0];
        var query = term.replace("?terms=","");
        document.getElementById("remote").value = query0;
        document.getElementById("form").submit();
    }
</script>
<body>
    <!-- MiniSearch -->
    <div class="row topBar">
        <form action="search" method="post">
            <div class="input-group mb-3">
                <a> <!--href="<s:url action="index" />"--><img src="./images/UC_Logo.png" alt="uc_logo" class="indexLogo"></a>
                <input type="text"
                       class="form-control searchInput"
                       placeholder="Web Search"
                       aria-describedby="button-addon2"
                       name = "browser.query">
                <button class="btn btn-outline-secondary searchButton" type="submit" id="button-addon2" >Search</button>
            </div>
        </form>
        <form action="yandex" method="post">
            <button class="btn btn-outline-secondary" type="submit">Translate</button>
        </form>
        <script>
        </script>
        <button class="btn btn-outline-secondary searchButton"><a href="<s:url action="sharePage" />">Share on FACEBOOK</a></button>
    </div>

    <!-- Resultados -->
    <c:forEach items="${browser.detailedResults}" var="result">
        <div class="card resultsCard">
            <div class="card-body">
                <h5 class="card-title"><a href="${result.url}" class="card-link resultTitle">${result.title}</a></h5>
                <h6 class="card-subtitle mb-2 text-muted resultLinkInfo">${result.url}</h6>
                <h6 class="card-subtitle mb-2 text-muted resultLinkInfo">Language: ${browser.lang}</h6>
                <p class="card-text">${result.description}.</p>
            </div>
        </div>
    </c:forEach>
</body>
</html>
