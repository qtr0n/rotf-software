# order/order.py
from concurrent import futures
import random
import grpc
import recommendations_pb2_grpc

from order_pb2 import (
    FoodCategory,
    FoodOrder,
    OrderResponse,
)

#Note: Only Indian Cuisine Category is mentioned below.

food_by_category = {
    FoodCategory.SOUTH_INDIAN: [
        FoodOrder(id=1, title="IDLI"),
        FoodOrder(id=2, title="DOSA"),
    ],
    FoodCategory.NORTH_INDIAN: [
        FoodOrder(id=3, title="Chole Bhature"),
        FoodOrder(id=4, title="Dal Makhani"),
    ],
}

#Class to implement the microservice functions.

class OrderService(order_pb2_grpc.OrderServicer):
    def Order(self, request, context):
        if request.category not in food_by_category:
            context.abort(grpc.StatusCode.NOT_FOUND, "Category not found")
        food_for_category = food_by_category[request.category]
        num_results = min(request.max_results, len(food_for_category))
        food_ordered = random.sample(food_for_category, num_results)
        return OrderResponse(order=food_ordered)

#To execute it, use the serve(): function.

def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    order_pb2_grpc.add_OrderServicer_to_server(OrderService(), server)
    server.add_insecure_port("[::]:50051")
    server.start()
    server.wait_for_termination()


if __name__ == "__main__":
    serve()