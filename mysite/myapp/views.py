from django.shortcuts import render
#from django import HttpResponse
from django.http import HttpResponse

from rest_framework import viewsets
from .serializers import ConditionsSerializer
from .models import Conditions
import requests
import matplotlib.pyplot as plt
from io import StringIO
import numpy as np




# Create your views here.
def createTempGraph(tempList):
    x=[]
    y=[]
    for idx, temp in enumerate(tempList[0:30]):
        y.append(temp.temperature)
        x.append(idx*10)
    fig = plt.figure()
    plt.plot(x, y, color="orange")
    plt.ylabel("Temperature")
    plt.xlabel("Time")
    plt.title("Temperature History")
    
    imgData = StringIO()
    fig.savefig(imgData, format='svg')
    imgData.seek(0)

    data = imgData.getvalue()
    return data


def createHumidityGraph(tempList):
    x = []
    y = []
    for idx, val in enumerate(tempList[0:30]):
        y.append(val.humidity)
        x.append(idx*10)
    fig = plt.figure()
    plt.plot(x, y)
    plt.ylabel("Humidity")
    plt.xlabel("Time")
    plt.title("Humidity History")

    imgData = StringIO()
    fig.savefig(imgData, format='svg')
    imgData.seek(0)

    data = imgData.getvalue()
    return data
    
    



def index(request):
    temp = Conditions.objects.all().last()
    

    temp_list = Conditions.objects.all()
    temp_list = temp_list[0:5]

    response = requests.get(f"http://api.openweathermap.org/data/2.5/weather?q=toronto&appid=b81347c5672e23b4e026a7533d499673")
    data = response.json()
    weather = int(round([data["main"]][0]["temp"] - 273.15))
    country = [data["name"]][0]

    tempGraph = createTempGraph(temp_list)
    humidGraph = createHumidityGraph(temp_list)
   

    context = {'temperature': temp, 'tempList': temp_list, 'weather': weather, 'country':country, 'tempgraph': tempGraph, "humidgraph": humidGraph}
    return render(request, 'index.html', context=context)



class ConditionView(viewsets.ModelViewSet):
    serializer_class = ConditionsSerializer
    queryset = Conditions.objects.all()
