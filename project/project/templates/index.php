{% load static %}

<head>
    <title>Bootstrap Example</title>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/css/bootstrap.min.css">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.4.1/js/bootstrap.min.js"></script>
</head>
{% block content %}


<div class="row">
    <div class="col-lg-2"></div>
    <div class="col-lg-8">
    <h2>Electricity bill : {{price}} unit</h2>
    <h2>From time {{ startdate}} {{ starttime}} to {{ enddate}} {{ endtime}}</h2>
        <form action="searchDB" method="get">
            <div class="form-group">
                <label for="usr">time start</label>
                <input type="date" class="form-control" name="startdate">
                <input type="time" class="form-control" name="starttime">
            </div>
            <div class="form-group">
                <label for="usr">time end</label>
                <input type="date" class="form-control" name="enddate">
                <input type="time" class="form-control" name="endtime">
            </div>
            <input type="submit" value="Search" class="btn btn-success" >
        </form>
    </div>
</div>

{% endblock%}