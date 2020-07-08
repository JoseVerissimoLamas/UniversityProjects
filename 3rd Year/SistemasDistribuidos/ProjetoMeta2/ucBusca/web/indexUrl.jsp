<%--
  Created by IntelliJ IDEA.
  User: Zé VL
  Date: 11/12/2019
  Time: 16:41
  To change this template use File | Settings | File Templates.
--%>
<%@ taglib prefix="s" uri="/struts-tags"%>
<%@ taglib prefix="d" uri="/struts-tags"%>
<%@ page language="java" contentType="text/html; charset=ISO-8859-1" pageEncoding="ISO-8859-1"%>
<html>
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">

    <link href="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-Vkoo8x4CGsO3+Hhxv8T/Q5PaXtkKtu6ug5TOeNV6gBiFeWPGFN9MuhOf23Q9Ifjh" crossorigin="anonymous">
    <script src="https://code.jquery.com/jquery-3.4.1.slim.min.js" integrity="sha384-J6qa4849blE2+poT4WnyKhv5vZF5SrPo0iEjwBvKU7imGFAV0wwj1yYfoRSJoZ+n" crossorigin="anonymous"></script>
    <script src="https://cdn.jsdelivr.net/npm/popper.js@1.16.0/dist/umd/popper.min.js" integrity="sha384-Q6E9RHvbIyZFJoft+2mJbHaEWldlvI9IOYy5n3zV9zzTtmI3UksdQRVvoxMfooAo" crossorigin="anonymous"></script>
    <script src="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/js/bootstrap.min.js" integrity="sha384-wfSDF2E50Y2D1uUdj0O3uMBJnjuUD4Ih7YwaYd1iqfktj0Uod8GCExl3Og8ifwB6" crossorigin="anonymous"></script>
    <link rel="stylesheet" href="styleSheet.css">

    <title>UcBusca: Index</title>
</head>
<body>

    <%@include file="header.jsp"%>

    <!-- Index Link -->
        <form action="indexUrl" method="post" class="searchBar">
            <div class="row" style="margin-bottom: 2%;">
                <h3 class="indexTitle">Index Link</h3>
            </div>
            <div class="input-group mb-3 row">
                <input type="text"
                       class="form-control"
                       placeholder="Web Search"
                       aria-describedby="button-addon2"
                       name = "index.link">
                <button class="btn btn-outline-secondary" type="submit" id="button-addon4">Index</button>
            </div>
        </form>

</body>
</html>
