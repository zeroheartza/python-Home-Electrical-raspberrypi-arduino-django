from django.shortcuts import render,redirect
from django.http import HttpResponse
from influxdb import InfluxDBClient
import datetime

def hello(request):
    #Query Data From Model
    #return HttpResponse('Heart')
    return render(request,'index.php',{'products':'heart'})


def searchDB(request):
    client = InfluxDBClient(host='localhost', port=8086)
    client.switch_database('mysampledb')

    # startdate = request.GET['startdate']
    # starttime = request.GET['starttime']
    # enddate = request.GET['enddate']
    # endtime = request.GET['endtime']
    startdate = str(request.GET['startdate'])
    starttime = str(request.GET['starttime'])+':00'
    enddate = str(request.GET['enddate'])
    endtime = str(request.GET['endtime'])+':00'
    querydb = ("\nSELECT * FROM cpu where time >= '{} {}' and time < '{} {}'").format(startdate,starttime,enddate,endtime)
    results = client.query(querydb)
    points = results.get_points(tags={'host': 'serverA'})
    data=0
    n=0

    # #test1
    # for i in points:
    #     data+= float(i['value'])
    #     n+=1
    # data= (data/n)
    # print(data)
    # print("{:.2f}".format(data))
    # print(startdate)
    # year, month, day  = list(map(int,startdate.split('-')))
    # hour, minute, second  = list(map(int,starttime.split(':')))
   
    # a = datetime.datetime(year, month, day, hour, minute, second)
    # year, month, day  = list(map(int,enddate.split('-')))
    # hour, minute, second  = list(map(int,endtime.split(':')))
   
    # b = datetime.datetime(year, month, day, hour, minute, second)
    # c = b-a

    # print('Difference: ', c)
    # minutes = c.total_seconds() / 60
    # print('Total difference in minutes: ', minutes)
    

   
    # price = "{:.2f}".format(data*(minutes/60)/1000)
    # print(price)

    #test2
    for i in points:
        data+= (float(i['value'])/(1000*60))
        n+=1

    price = "{:.6f}".format(data)


    return render(request,'index.php',{'startdate':startdate,'starttime':starttime,'enddate':enddate,'endtime':endtime,'price':price})