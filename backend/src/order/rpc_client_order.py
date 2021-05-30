import grpc
from order_pb2_grpc import OrderStub

client = OrderStub(channel)
request = OrderRequest(user_id=1, category=FoodCategory.SOUTH_INDIAN, max_results=3)
request.category
channel = grpc.insecure_channel("localhost:50051")
client.Order(request)