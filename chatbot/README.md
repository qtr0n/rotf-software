
## Chatbot Using Rasa Framework


The popularity of live chat applications has been growing over the past few years. And as the AI trend keeps rising, chatbots become more a must-have rather than a nice to have part of the business. The increasing demand for chats continues to grow so to keep the customer satisfaction rate high; companies must find ways to cope with the rising volumes of inquiries coming every day to all their communication channels.

Chatbots have no competition when it comes to turnout and motivation. They never get tired, bored or distracted.
> __Chatbots are getting - smarter, more accessible and useful.__


### The Architecture of chatbot 

![https://chatbotsmagazine.com/the-ultimate-guide-to-designing-a-chatbot-tech-stack-333eceb431da](https://miro.medium.com/max/1078/1*BVBQ-uiAOYB9LthbSoiUUA.png "Logo Title Text 1")

Read more about it [here](https://blog.vsoftconsulting.com/blog/understanding-the-architecture-of-conversational-chatbot)


### What is Rasa?
[Rasa](https://rasa.com/docs/rasa/) is an open-source machine learning framework for building [contextual AI assistants and chatbots](https://blog.rasa.com/level-3-contextual-assistants-beyond-answering-simple-questions/).  
To make complete AI-based chatbot it has to handle two things: 

* Understanding the user’s message which is done through Rasa [NLU](https://rasa.com/docs/rasa/nlu/about/).
* The bot should be able to carry dialogue with context which is done by Rasa [Core](https://rasa.com/docs/rasa/core/about/).

So how does rasa handles such tasks. It is done through various elements of the RASA. Let’s look at the architecture of the RASA.

![Conversation diagram](https://lh4.googleusercontent.com/vglDus-TNUadCP-JJvCHOGwUkn4NdTD6balsubtO-Q9CO6nlR1u1x8egD_dWZSNSmf98ArqjCYVhCxZAfZ_RrJOM-Dx1cn56N5oAiWoPMc35LYY2DS0uVyz1W5DsIQzkfU23Bcob)

### Setup and installation instructions:

* Download and install anaconda: https://docs.anaconda.com/anaconda/install/ 
* Create a conda virtual environment: https://uoa-eresearch.github.io/eresearch-cookbook/recipe/2014/11/20/conda/
* Install RASA : https://rasa.com/docs/rasa/user-guide/installation/#quick-installation
and other missing dependency(spacy) : https://rasa.com/docs/rasa/user-guide/installation/#dependencies-for-spacy

Go through this quick RASA tutorial: https://rasa.com/docs/rasa/user-guide/rasa-tutorial/ for quick setup.

### Chatting with Bot
You can download Pre-trained model from [here](https://drive.google.com/drive/folders/1mqAZRJoo7AfC9Gp1IdK8gHkLujpM7yEX?usp=sharing) and put it in models folder. As it has a large size it can't be uploaded on Github.

### - Steps to chat with pre-trained bot: 
```
- CLI-1
-- rasa run actions
- CLI-2
-- rasa shell
```
### - Steps to interactively train:
```
- CLI-1
-- rasa run actions
- CLI-2
-- rasa interactive
```

You can also train your own model

### - Steps to train and run rasa model 
```
- CLI-1
-- rasa train
- CLI-2
-- rasa shell
```
### [Examples images](https://github.com/theobscuredev/rotf-software/tree/main/chatbot/Assets/Images) from our training:
<p float="center">
  <img src="https://github.com/theobscuredev/rotf-software/blob/main/chatbot/Assets/Images/A3.PNG" width="400" height="250" />
  <img src="https://github.com/theobscuredev/rotf-software/blob/main/chatbot/Assets/Images/A4.PNG" width="400" height="250" />
  <img src="https://github.com/theobscuredev/rotf-software/blob/main/chatbot/Assets/Images/A5.PNG" width="400" height="250" /> 
</p>

A short video can be viewed [here](https://github.com/theobscuredev/rotf-software/tree/main/chatbot/Assets/Videos)

### Connecting Chatbot to Broker server

Our chat bot consists of Entities and Slots. Entities are those pieces of information we want to to extract from our conversation and Slots are the variables we use to store them. In this chatbot we have used:
* Cuisine
* Dish
* Number of a particular dish

as entities and slots. We can easily pass these values to the broker server using python commands.
