<%@ taglib prefix="s" uri="/struts-tags" %>
<%--
  Created by IntelliJ IDEA.
  User: Zé VL
  Date: 08/12/2019
  Time: 12:20
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>UcBusca Indexing...</title>
</head>
<body>
    <%@include file="header.jsp"%>
    <p>Indexing: ${index.link} ...</p>
    <p><a href="<s:url action="index" />">Start</a></p>
</body>
</html>
