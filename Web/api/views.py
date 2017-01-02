from django.http import HttpResponse, Http404
from django.shortcuts import render
from django.template import loader

from .models import Coordinator


def index(request):
    return HttpResponse(request, "Test")
