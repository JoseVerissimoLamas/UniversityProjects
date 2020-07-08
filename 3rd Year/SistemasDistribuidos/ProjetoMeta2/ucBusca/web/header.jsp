<%--
  Created by IntelliJ IDEA.
  User: Z� VL
  Date: 12/12/2019
  Time: 18:46
  To change this template use File | Settings | File Templates.
--%>

<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">

<link href="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-Vkoo8x4CGsO3+Hhxv8T/Q5PaXtkKtu6ug5TOeNV6gBiFeWPGFN9MuhOf23Q9Ifjh" crossorigin="anonymous">
<script src="https://code.jquery.com/jquery-3.4.1.slim.min.js" integrity="sha384-J6qa4849blE2+poT4WnyKhv5vZF5SrPo0iEjwBvKU7imGFAV0wwj1yYfoRSJoZ+n" crossorigin="anonymous"></script>
<script src="https://cdn.jsdelivr.net/npm/popper.js@1.16.0/dist/umd/popper.min.js" integrity="sha384-Q6E9RHvbIyZFJoft+2mJbHaEWldlvI9IOYy5n3zV9zzTtmI3UksdQRVvoxMfooAo" crossorigin="anonymous"></script>
<script src="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/js/bootstrap.min.js" integrity="sha384-wfSDF2E50Y2D1uUdj0O3uMBJnjuUD4Ih7YwaYd1iqfktj0Uod8GCExl3Og8ifwB6" crossorigin="anonymous"></script>
<link rel="stylesheet" href="styleSheet.css">

<div class="indexHeader">
    <a href="<s:url action="index"/>">Main Page</a>
    <d:if test="%{ClientBean.log == 'yes'}">
        <a id="username">${ClientBean.username}</a>
        <d:if test="%{ClientBean.Admin}">
            <a href="admin.jsp">Admin Page</a>
            <a href="<s:url action="indexAnUrl"/>">Index</a>
            <a href="<s:url action="searchAparent"/>">SearchParent</a>
            <a href="<s:url action="givepage"/>">Give Prev.</a>
        </d:if>
        <a href="<s:url action="history" />" >History</a>
        <a href="<s:url action="logout"/>">Logout</a>
    </d:if>
    <d:else>
        <a href="login.jsp">LOGIN</a>
        <a href="register.jsp">REGISTER</a> <br>
    </d:else>
</div>