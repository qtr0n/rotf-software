# master/master.py

import os
from flask import Flask, render_template
import grpc

from order_pb2 import FoodCategory, OrderRequest
from order_pb2_grpc import OrderStub

app = Flask(__name__)

order_host = os.getenv("ORDER_HOST", "localhost")
order_channel = grpc.insecure_channel(
    f"{order_host}:50051"
)
order_client = OrderStub(order_channel)


@app.route("/")
def render_homepage():
    order_request = OrderRequest(
        user_id=1, category=FoodCategory.SOUTH_INDIAN, max_results=3)
    order_response = order_client.Order(order_request)
    return render_template("homepage.html",order=order_response.order)