from typing import Any, Text, Dict, List
from rasa_sdk import Action, Tracker
from rasa_sdk.executor import CollectingDispatcher
import requests
import ast
from rasa_sdk.events import SlotSet
import requests
import ast





class ActionDishName(Action):
    def name(self):
        return "action_set_dish"
    def run(self, dispatcher: CollectingDispatcher, 
            tracker: Tracker,
            domain: Dict[Text, Any] ) -> List[Dict[Text, Any]]:    
        dispatcher.utter_message(template="utter_ask_number")
        return [SlotSet('dish', tracker.latest_message["text"])]4
        

class ActionDishNumber(Action):
    def name(self):
        return "action_set_number"
    def run(self, dispatcher: CollectingDispatcher, 
            tracker: Tracker,
            domain: Dict[Text, Any] ) -> List[Dict[Text, Any]]:    
        dispatcher.utter_message(template="utter_affirm_info")
        return [SlotSet('number', tracker.latest_message["text"])]






