# RenderBuddy
A handy tool and a guide to get your Unreal Engine capable of handling remote connections to control renders plus batch rendering and a few other things.

## Philosophy
While Unreal is very robust in the capabilities which can be applied to it. There is a gap between individuals/small-teams/freelancers and the big scale corporations. While, big teams are able to leverage the entire capability of Unreal and it's extensions, making use of new process/new thread renders or remote control or batching together renders - there is a gap in which the smaller teams are unable to fully utilize Unreal and bring themselves a lot of hassle whether that be because of time constraints or a non-technical orientation. This small tool hopes to bridge that gap quickly and get them up and running without disrupting their workflows.

![image.png](https://raw.githubusercontent.com/sudotman/sudotman/refs/heads/main/demos/RenderBuddy/BuddyMain.png)

# **User Guide: Configuring RenderBuddy with Firebase and Unreal Engine**

This guide will walk you through setting up **Firebase Realtime Database** and **Firebase Hosting** to track and display render status online for your Unreal Engine project.

---

## **Step 1: Setting Up Firebase**

1. **Create a Firebase Project**
    - Go to [Firebase Console](https://console.firebase.google.com/).
    - Click on **"Add Project"**.
    - Enter a project name (e.g., `RenderStatusTracker`), and click **Continue**.
    - Disable Google Analytics unless you need it, and click **Create Project**.
2. **Enable Realtime Database**
    - Once the project is created, navigate to **"Build"** > **"Realtime Database"** on the left sidebar.
    - Click **"Create Database"**.
    - Choose the region closest to you, and set the database to **Test Mode** (so anyone can read and write temporarily).
    - Click **"Enable"** to initialize the database.
3. **Create Firebase Realtime Database Rules**
    - In the **Database** section, click on **"Rules"**.
    - Set rules for your database to allow public read/write access temporarily during testing. Later, this can be tightened.
        
        ```json
        {
          "rules": {
            ".read": true,
            ".write": true
          }
        }
        
        ```
        
    - Click **Publish**.
4. **Get Firebase Configuration**
    - In the Firebase Console, go to **Project Settings** (gear icon in the upper left).
    - Scroll down to **Your Apps** and click on **</> (Web)** to register your app as a web app.
    - Give it a name (e.g., `RenderTrackerApp`) and click **Register App**.
    - Firebase will provide you with a config snippet like this:
        
        ```jsx
        const firebaseConfig = {
          apiKey: "your-api-key",
          authDomain: "your-project-id.firebaseapp.com",
          databaseURL: "<https://your-project-id.firebaseio.com>",
          projectId: "your-project-id",
          storageBucket: "your-project-id.appspot.com",
          messagingSenderId: "your-sender-id",
          appId: "your-app-id"
        };
        
        ```
        

---

## **Step 2: Configure Unreal Engine to Send Render Status to Firebase**

### Prerequisites

1. Open your Unreal Engine project.
2. Go to **Edit > Plugins**.
3. Search for `HttpBlueprint`, enable the plugin.
4. **Ensure you link your Firebase URL to the Base App URL variable in the Utility Widget**: Set the URL to your Firebase Realtime Database endpoint:

```
<https://your-project-id.firebaseio.com/renderstatus.json>
```

![image.png](https://raw.githubusercontent.com/sudotman/sudotman/refs/heads/main/demos/RenderBuddy/BuddyBaseAppURL.png)

The utility widget features a “SendRenderStatusToFirebase” which should be ideally used for a quick setup.

If you want a more manual blueprint setup, follow the guide below:

### **Manual Blueprint Setup for Sending Render Status:**

1. **Create a Blueprint Actor** (or use an existing one).
2. Add an event (e.g., `On Render Started`) where you want to trigger the status update.

### **OnRenderStarted (HttpBlueprint Node Manual Setup / Starting Point):**

- Add the **Http Post Request** node to send data to Firebase.

Here’s the breakdown:

1. **Make HTTP Post Request**:
    - **URL**: Set the URL to your Firebase Realtime Database endpoint:
        
        ```
        <https://your-project-id.firebaseio.com/renderstatus.json>
        ```
        
    
2. **Prepare Data in JSON Format**:
    - Use the `Format Text` node to create a JSON object [parentheses are appended to the beginning and the end after the formatted text]:
        
        ```
        
          "status":"{Status}",
          "progress":{Progress}
        ```
        
    - Replace `{Status}` with your render status (e.g., `"rendering"`), and `{Progress}` with a progress value (e.g., `50`).
3. **Add Request Headers**:
    - Add a header to specify that the content is JSON:
        - Use **Make Request Header** with the following key-value:
            - `Json Request`.

---

## **Step 3: Setting Up Firebase Hosting for the Status Dashboard**

1. **Install Firebase CLI**
    - Open a terminal and install the Firebase CLI globally:
        
        ```bash
        npm install -g firebase-tools
        ```
        
2. **Login to Firebase**
    - After installation, log into your Firebase account:
        
        ```bash
        firebase login
        ```
        
3. **Initialize Firebase Hosting**
    - Navigate to your project folder in the terminal and run:
        
        ```bash
        firebase init hosting
        ```
        
    - Select the Firebase project you created earlier (`RenderStatusTracker`).
    - Choose the default public directory (e.g., `public`).
4. **Create Simple Web Dashboard**
In the `public` folder, create a simple `index.html` file to display the render status:
    
    ```html
    <!DOCTYPE html>
    <html lang="en">
    <head>
      <meta charset="UTF-8">
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
      <title>Render Status Dashboard</title>
      
      <!-- Firebase App (the core Firebase SDK) -->
      <script src="https://www.gstatic.com/firebasejs/9.6.11/firebase-app-compat.js"></script>
      <!-- Firebase Realtime Database -->
      <script src="https://www.gstatic.com/firebasejs/9.6.11/firebase-database-compat.js"></script>
    
      <style>
        body {
          font-family: Arial, sans-serif;
          background-color: #f4f4f9;
          margin: 0;
          padding: 0;
          display: flex;
          justify-content: center;
          align-items: center;
          height: 100vh;
        }
    
        .dashboard {
          background-color: #fff;
          border-radius: 10px;
          box-shadow: 0px 4px 10px rgba(0, 0, 0, 0.1);
          padding: 40px;
          max-width: 400px;
          text-align: center;
        }
    
        h1 {
          font-size: 24px;
          color: #333;
          margin-bottom: 20px;
        }
    
        p {
          font-size: 18px;
          color: #555;
          margin: 10px 0;
        }
    
        .status {
          font-size: 22px;
          font-weight: bold;
          color: #3498db;
        }
    
        .progress {
          font-size: 22px;
          font-weight: bold;
          color: #27ae60;
        }
    
        .progress-bar {
          background-color: #f4f4f9;
          border: 1px solid #ccc;
          border-radius: 20px;
          height: 30px;
          margin-top: 10px;
          width: 100%;
          position: relative;
          overflow: hidden;
        }
    
        .progress-bar-inner {
          background-color: #27ae60;
          height: 100%;
          border-radius: 20px;
          width: 0;
          transition: width 0.4s ease;
        }
      </style>
    </head>
    <body>
      <div class="dashboard">
        <h1>Render Status Dashboard</h1>
        
        <p>Status: <span class="status" id="status">N/A</span></p>
        <p>Progress: <span class="progress" id="progress">0%</span></p>
        
        <div class="progress-bar">
          <div class="progress-bar-inner" id="progress-bar-inner"></div>
        </div>
      </div>
    
      <script>
        // Your Firebase configuration
        const firebaseConfig = {
            apiKey: "your-api-key",
            authDomain: "your-project-id.firebaseapp.com",
            databaseURL: "<https://your-project-id.firebaseio.com>",
            projectId: "your-project-id",
            storageBucket: "your-project-id.appspot.com",
            messagingSenderId: "your-sender-id",
            appId: "your-app-id"
        };
    
        // Initialize Firebase
        firebase.initializeApp(firebaseConfig);
        
        // Reference to the database
        const database = firebase.database();
    
        // Reference to the 'renderstatus' node
        const renderStatusRef = database.ref("renderstatus");
    
        // Listen for value changes
        renderStatusRef.on("value", (snapshot) => {
          const data = snapshot.val();
          if (data) {
            // Get the latest entry (Firebase auto-generates keys)
            const keys = Object.keys(data);
            const latestKey = keys[keys.length - 1];
            const latestData = data[latestKey];
    
            // Update the web page
            document.getElementById("status").innerText = latestData.status;
            const progress = latestData.progress;
            document.getElementById("progress").innerText = `${progress}%`;
    
            // Update the progress bar
            document.getElementById("progress-bar-inner").style.width = `${progress}%`;
          }
    	  else{
            document.getElementById("status").innerText = "No Data";
            document.getElementById("progress").innerText = "0%";
    
            // Update the progress bar
            document.getElementById("progress-bar-inner").style.width = 0;
    	  }
        });
      </script>
    </body>
    </html>
    
    ```

5. **Deploy to Firebase Hosting**
    - To deploy the web dashboard:
        
        ```bash
        firebase deploy
        ```
        
    
    Firebase will provide a hosting URL where the status page is live, such as `https://your-project-id.web.app`.

This is how it will look like once the setup is properly done [the status message might vary]: <br>
![BuddyFirebase.png](https://raw.githubusercontent.com/sudotman/sudotman/refs/heads/main/demos/RenderBuddy/BuddyFirebase.png)

    

---

## **Step 4: Testing the Configuration**

1. **Test Render Status Updates**
    - Run your Unreal project and trigger render status updates.
    - The render status should now be visible on your Firebase-hosted dashboard.
2. **Secure the Firebase Database**
    - After testing, go back to **Database Rules** in Firebase and update them to restrict public access, allowing only authenticated users or specific roles to read/write status updates.

---

## **Step 5: Having fun and other general tips!**

1. **Batch Renders**
    - Batch renders work with a specified CSV file, a sample one is already present in the project.
    - Press on ‘refresh CSV data’ if the batch render’s “start index”/”total render” doesn’t update automatically.
    - Click ‘Render in PIE’ and all your renders depending on the excel file will execute in batch!

![BuddyBatchSettings.png](https://raw.githubusercontent.com/sudotman/sudotman/refs/heads/main/demos/RenderBuddy/BuddyBatchSettings.png)

2. **Render in a new process plus config**
    - Since, PIE renders usually take up extra resources since the Editor remains open - you can use new process renders which will automatically start a new process thread that will
    - Press on ‘render in new process’ to start the current sequence selected to render in a new process.
    - Click ‘Apply Overrides’ and all the override settings will be applied instead of the MoviePipelineConfig object settings.

![BuddyConfig.png](https://raw.githubusercontent.com/sudotman/sudotman/refs/heads/main/demos/RenderBuddy/BuddyConfig.png)

3. **Remote Settings**
    - To debug the proper workings of the tool, press on ‘Force Send Status to DB’ and check your firebase website to see if the changes have been reflected.
    - Press on ‘Force Get Status From DB’ to force fetch the last saved status on the DB - can be useful when debugging, again.
    - Check connection updates the status by performing both the actions. Always press it atleast once until the ‘Current Status’ shows “Connected”.
    
    ![BuddyRemote.png](https://raw.githubusercontent.com/sudotman/sudotman/refs/heads/main/demos/RenderBuddy/BuddyRemote.png)
    

Created by Satyam Kashyap.