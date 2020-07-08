<%@ taglib prefix="s" uri="/struts-tags"%>
<%@ taglib prefix="d" uri="/struts-tags"%>
<%@ page language="java" contentType="text/html; charset=ISO-8859-1" pageEncoding="ISO-8859-1"%>
<html>
<head>
    <title>Register</title>
</head>

<body>

<%@include file="header.jsp"%>

<h2>Register</h2>

<s:form action="register" method="post">
    <s:fielderror fieldName="clientBean.username"/>
    <s:textfield name="clientBean.username" label="Username"/><br>
    <s:fielderror fieldName="clientBean.password"/>
    <s:password name="clientBean.password" label="Password"/><br>
    <s:submit/>
</s:form>
<p>${ClientBean.message}</p>
<p><a href="<s:url action="index"/>">BACK</a></p>

</body>
</html>
