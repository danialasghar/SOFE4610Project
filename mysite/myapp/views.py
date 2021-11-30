from django.shortcuts import render
#from django import HttpResponse
from django.http import HttpResponse

from rest_framework import viewsets
from .serializers import ConditionsSerializer
from .models import Conditions

# Create your views here.
def index(request):
    temp = Conditions.objects.all().last()

    temp_list = Conditions.objects.all()
   

    context = {'temperature': temp, 'tempList': temp_list}
    return render(request, 'index.html', context=context)



class ConditionView(viewsets.ModelViewSet):
    serializer_class = ConditionsSerializer
    queryset = Conditions.objects.all()
