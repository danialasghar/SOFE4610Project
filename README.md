# SOFE4610Project Group 7
## Django Web Server for Smart Thermostat 
### Danial Asghar, Yusuf Shaik, Hamza Farhat 

#### Table of Contents

- [Deployment](https://github.com/danialasghar/SOFE4610Project/tree/main/Deployment) Contains screenshots of the system execution and the code
    <details>
    <summary>Click to Expand Details</summary>

    - Screenshots
        - Digital Ocean Droplet.png - Shows the details of the DO droplet which holds the server.
        - Digital Ocean Virtual Host Linkage.png - Displays the virtual host connection between the IP address and the domain name.
        - Django API.png - Shows the Django API endpoints.
        - Django SQLite DB.png - Shows the SQLite database administration page, displaying one of the existing entries under the conditions table. 
        - Node-Red Pipeline.png - Shows the Node-Red pipline for the droplet. The pipeline has an incoming post endpoint which captures data and sends it to the mosquitto broker running on the server. The subscription then listens to the data, message is parsed into the valid json and inserted into SQLite. 
    - Code
        - arduino_code.ino - NodeMCU sketch for conducting readings and sending post request to HTTPS. 
        - group7iot.com.conf - Apache Server configuration file for the project which accepts HTTP and HTTPS traffic.
        - mosquitto.conf - The Mosquitto broker configuration file. 
    </details>

- [Django Server](https://github.com/danialasghar/SOFE4610Project/tree/main/Django%20Server) Contains code for the Django deployment which displays the frontend and creates the DB instance
    <details>
    <summary>Click to Expand Details</summary>

    - /myapp - This contains the bulk of the code of our API
        - migrations
            - 0001_initial - Migration file to create the SQLlite database using the provided columns; i.e. id, temperature, humidity. 
        - templates
            - index.html - The Index page accessible at ip:port/app which shows the Temperature and Humidity.
        - admin - It reads metadata from your models to provide a quick, model-centric interface where trusted users can manage content on your site.
        - apps - This file is created to help the user include any application configuration for the app. We set the name of our app in there.
        - models- Lists the database models to be used in the application. We use model: Conditions with two properties: Temperature and Humidity.
        - serializers - Serializers allow complex data such as querysets and model instances to be converted to native Python datatypes that can then be easily rendered into JSON, XML or other content types. We define our model and its fields in the serializer.
        - tests - Can be used to write test cases; we did not write any tests for this application. 
        - urls - Defines the site URL to view mapping, for our application the mysite/urls.py is used instead. 
        - views - A view function, or view for short, is a Python function that takes a Web request and returns a Web response. Our view has a definition for index which is used to retrieve the value from the Database and rendered into the index.html
    - /mysite
        - urls - Defines the site URL to view mapping, for us these include /app, /api and /admin
        - settings - Contains all the website settings, including registering any applications we create, the location of our static files, database configuration details, etc. We had to edit the ALLOWED_HOSTS and set it to * so that any incoming request (nodemcu) could connect.
        - __init__ - is an empty file that instructs Python to treat this directory as a Python package.
        - wsgi - is used to help your Django application communicate with the webserver.
        - asgi - is a standard for Python asynchronous web apps and servers to communicate with each other.

- [IoT Design Methodology](https://github.com/danialasghar/SOFE4610Project/tree/main/IoT%20Design%20Methodology) Contains the IoT Design metholodogy steps created in Assignment 2
    <details>
    <summary>Click to Expand Details</summary>

    - Purpose and Specification - Step 1/10: Define purpose and requirements of the IoT system.
    - Process Specification - Step 2/10: Defines the use cases.
    - Domain Model Specification - Step 3/10: Describes the main concepts, entities and objects in the domain of the Smart Thermostat. 
    - Information Model Specification - Step 4/10: Defines the structure of all the information within the system.
    - Service Specifications - Step 5/10: Defines the services in the Smart Thermostat system. 
    - IoT Level Specification - Step 6/10: Defines the IoT levels of the system.
    - Functional View Specification - Step 7/10: Defines the functions of the Smart Thermostat grouped into Functional Groups
    - Operational View Specification - Step 8/10: Defines various options pertaining to the Smart Thermostat's Deployment and operation. 
    - IoT Layers - The over-arching deployment diagram of the full system, seperating modules into their various IoT layers.
    </details>

- [Presentation](https://github.com/danialasghar/SOFE4610Project/tree/main/Presentation) Contains the final presentation file

- [Screenshots and Videos](https://github.com/danialasghar/SOFE4610Project/tree/main/Screenshots%20and%20Video) Contains the screenshots of the frontend during execution and link to video recording
    <details>
    <summary>Click Here to Expand Details</summary>

    - Frontend1.png - Screenshot of the Django front-end view displaying current and historical weather data.
    - Frontend2.png - Screenshot of Temperature history on the front-end which is created using Matplotlib.
    - Frontend3.png - Screenshot of Humidity history on the front-end which is created using Matplotlib.
    - HardwareVideo.txt - Contains the Google Drive link which was the hardware demonstration which we displayed in the presentation.
    </details>

- Final Report.pdf - Final report containing Architectural design decisions and test cases. 



