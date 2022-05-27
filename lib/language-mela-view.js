'use babel';
import { CompositeDisposable, Disposable} from 'atom';

export default class LanguageMelaView {

  constructor(serializedState) {

    // Create root element
    this.element = document.createElement('div');
    this.element.classList.add('language-mela');

    //var tooltipsSubscriptions = new CompositeDisposable();

    // Add buttons
    var buttonBlock = document.createElement("div")
    buttonBlock.setAttribute("class", "block")
    
    var buttonPanel = document.createElement("atom-panel");
    buttonPanel.setAttribute("class", "padded");
    
    var buttonGroup = document.createElement("div")
    buttonGroup.setAttribute("class", "btn-group btn-group-lg")
    this.element.appendChild(buttonGroup);

    var parseButton = document.createElement("button");
    parseButton.setAttribute("class", "btn mela-btn");
    parseButton.classList.add("selected"); // Opened by default
    parseButton.innerHTML = "Parse";
    buttonGroup.appendChild(parseButton);

    var analysisButton = document.createElement("button");
    analysisButton.setAttribute("class", "btn mela-btn");
    analysisButton.innerHTML = "Analysis";
    buttonGroup.appendChild(analysisButton);

    var simulationButton = document.createElement("button");
    simulationButton.setAttribute("class", "btn mela-btn");
    simulationButton.innerHTML = "Simulation";
    buttonGroup.appendChild(simulationButton);

    buttonPanel.appendChild(buttonGroup);
    buttonBlock.appendChild(buttonPanel);
    this.element.appendChild(buttonBlock)

    // Add line break
    //this.element.appendChild(document.createElement("br"))


    // Add compilation tab
    var compilationTab = document.createElement("div");
    compilationTab.setAttribute("class", "mela-tab");

    var javacCompilPanel = document.createElement("atom-panel");
    javacCompilPanel.setAttribute("class", "padded");
    var javacCompilPanelInset = document.createElement("div");
    javacCompilPanelInset.setAttribute("class", "inset-panel padded");
    javacCompilPanelInset.innerHTML = "Open a .mela file"
    javacCompilPanel.appendChild(javacCompilPanelInset);
    compilationTab.appendChild(javacCompilPanel);
    //compilationTab.innerHTML = "<div class='block'><atom-text-editor mini></atom-text-editor></div>"
    this.element.appendChild(compilationTab);




    // Add analysis tab
    var analysisTab = document.createElement("div");
    analysisTab.setAttribute("class", "mela-tab");
    analysisTab.setAttribute("style", "display: none");

    var panelsHeading = [];
    var panelsBody = [];

    // TODO: function addPanels() {}
    for (let i = 0; i < 3; i++) {
      let panel = document.createElement("atom-panel");
      panel.setAttribute("class", "padded");
      let panelInset = document.createElement("div");
      panelInset.setAttribute("class", "inset-panel");
      let panelHeading = document.createElement("div");
      panelHeading.setAttribute("class", "panel-heading");
      let panelBody = document.createElement("div");
      panelBody.setAttribute("class", "panel-body padded");

      panelsHeading.push(panelHeading)
      panelsBody.push(panelBody)

      panelInset.appendChild(panelHeading);
      panelInset.appendChild(panelBody);
      panel.appendChild(panelInset);
      analysisTab.appendChild(panel);
    }

    this.element.appendChild(analysisTab);

    panelsHeading[0].innerHTML = "<span class='icon icon-clock'></span>"
    panelsBody[0].innerHTML = "Open a .mela file"
    panelsHeading[1].innerHTML = "<span class='icon icon-plug'></span>"
    panelsBody[1].innerHTML = "Open a .mela file"
    panelsHeading[2].innerHTML = "<span class='icon icon-radio-tower'></span>"
    panelsBody[2].innerHTML = "Open a .mela file"

    //TODO: Add RAM


    // Add simulation tab
    var simulationTab = document.createElement("div");
    simulationTab.setAttribute("class", "mela-tab");
    simulationTab.setAttribute("style", "display: none");

    var simulationPanel = document.createElement("atom-panel");
    simulationPanel.setAttribute("class", "padded");

    var simulationPanelInset = document.createElement("div");
    simulationPanelInset.setAttribute("class", "inset-panel padded");


    var inputSimBlock = document.createElement("block");
    var inputSimButton = document.createElement("button");
    inputSimButton.setAttribute("class", "btn btn-sm");
    inputSimButton.innerHTML = "Browse..."
    var inputSimPath = document.createElement("div");

    var outputSimBlock = document.createElement("block");
    var outputSimButton = document.createElement("button");
    outputSimButton.setAttribute("class", "btn btn-sm");
    outputSimButton.innerHTML = "Browse..."
    var outputSimPath = document.createElement("div");
    outputSimPath.innerHTML = "choose a path"

    var postProcessSimBlock = document.createElement("block");
    //postProcessSimBlock.innerHTML = "<label class='input-label'><input class='input-checkbox' id='postprocess-checkbox' type='checkbox' checked></label>"
    var postProcessSimLabel = document.createElement("label");
    postProcessSimLabel.setAttribute("class", "input-label");
    var postProcessSimCheckbox = document.createElement("input");
    postProcessSimCheckbox.setAttribute("class", "input-checkbox");
    postProcessSimCheckbox.setAttribute("id", "postprocesscheckbox");
    postProcessSimCheckbox.setAttribute("type", "checkbox");
    postProcessSimCheckbox.setAttribute("checked", "");
    //postProcessSimCheckbox.innerHTML = "Hello"
    postProcessSimLabel.appendChild(postProcessSimCheckbox); 

    var postProcessSimButton = document.createElement("button");
    postProcessSimButton.setAttribute("class", "btn btn-sm");
    postProcessSimButton.innerHTML = "Browse..."
    var postProcessSimPath = document.createElement("div");
    postProcessSimPath.innerHTML = "choose a path"


    var generateOptionSimBlock = document.createElement("block");
    //postProcessSimBlock.innerHTML = "<label class='input-label'><input class='input-checkbox' id='postprocess-checkbox' type='checkbox' checked></label>"
    var generateOptionSimLabel = document.createElement("label");
    generateOptionSimLabel.setAttribute("class", "input-label");
    var generateOptionSimCheckbox = document.createElement("input");
    generateOptionSimCheckbox.setAttribute("class", "input-checkbox");
    generateOptionSimCheckbox.setAttribute("id", "generateoptioncheckbox");
    generateOptionSimCheckbox.setAttribute("type", "checkbox");
    generateOptionSimCheckbox.setAttribute("unchecked", "");
    //postProcessSimCheckbox.innerHTML = "Hello"
    generateOptionSimLabel.appendChild(generateOptionSimCheckbox);


    var runSimButton = document.createElement("button");
    runSimButton.setAttribute("class", "btn mela-sim-btn btn-info inline-block-tight icon icon-triangle-right");
    runSimButton.innerHTML = "Run";



    //var stopSimButton = document.createElement("button");
    //stopSimButton.setAttribute("class", "btn mela-sim-btn btn-info inline-block-tight icon icon-primitive-square");
    //stopSimButton.innerHTML = "Stop";

    var runPanel = document.createElement("atom-panel");
    runPanel.setAttribute("class", "padded");
    var runPanelInset = document.createElement("div");
    runPanelInset.setAttribute("class", "inset-panel padded");

    var cmakeDiv = document.createElement("div");
    cmakeDiv.innerHTML = "Run command \"cmake\":</br>"
    cmakeDiv.innerHTML += "<span class='inline-block highlight-warning'>Waiting</span>"
    var makeDiv = document.createElement("div");
    makeDiv.innerHTML = "</br>Run command \"make\":</br>"
    makeDiv.innerHTML += "<span class='inline-block highlight-warning'>Waiting</span>"
    var simDiv = document.createElement("div");
    simDiv.innerHTML = "</br>Run simulation:</br>"
    simDiv.innerHTML += "<span class='inline-block highlight-warning'>Waiting</span>"
    var postProcessDiv = document.createElement("div");
    postProcessDiv.innerHTML = "</br>Run post-processing:</br>"
    postProcessDiv.innerHTML += "<span class='inline-block highlight-warning'>Waiting</span>"

    inputSimBlock.innerHTML = "Input directory: "
    inputSimBlock.appendChild(inputSimButton);
    inputSimBlock.appendChild(inputSimPath);

    outputSimBlock.innerHTML = "Output directory: "
    outputSimBlock.appendChild(outputSimButton);
    outputSimBlock.appendChild(outputSimPath);

    postProcessSimBlock.appendChild(postProcessSimLabel);
    postProcessSimBlock.innerHTML += "Post-processing script: "
    postProcessSimBlock.appendChild(postProcessSimButton);
    postProcessSimBlock.appendChild(postProcessSimPath);
    
    generateOptionSimBlock.appendChild(generateOptionSimLabel);
    generateOptionSimBlock.innerHTML += "Disable code generation before compilation"

    simulationPanelInset.appendChild(inputSimBlock);
    simulationPanelInset.appendChild(document.createElement("br"));
    simulationPanelInset.appendChild(outputSimBlock);
    simulationPanelInset.appendChild(document.createElement("br"));
    simulationPanelInset.appendChild(postProcessSimBlock);
    simulationPanelInset.appendChild(document.createElement("br"));
    simulationPanelInset.appendChild(generateOptionSimBlock);
    simulationPanelInset.appendChild(document.createElement("br"));
    simulationPanelInset.appendChild(document.createElement("br"));
    simulationPanelInset.appendChild(runSimButton);
    //simulationPanelInset.appendChild(stopSimButton);

    simulationPanel.appendChild(simulationPanelInset);

    runPanelInset.appendChild(cmakeDiv)
    runPanelInset.appendChild(makeDiv)
    runPanelInset.appendChild(simDiv)
    runPanelInset.appendChild(postProcessDiv)
    runPanel.appendChild(runPanelInset);

    simulationTab.appendChild(simulationPanel);
    simulationTab.appendChild(runPanel);

    this.element.appendChild(simulationTab);

    /*
    var cpuResults = document.createElement("div");
    cpuResults.setAttribute("class", "results");
    cpuResults.innerHTML = "CPU analysis"
    this.element.appendChild(cpuResults);

    var energyResults = document.createElement("div");
    energyResults.setAttribute("class", "results");
    energyResults.innerHTML = "Energy analysis"
    energyResults.setAttribute("style", "display: none"); // Hidden by default
    this.element.appendChild(energyResults);

    var dataResults = document.createElement("div");
    dataResults.setAttribute("class", "results");
    dataResults.innerHTML = "Data analysis"
    dataResults.setAttribute("style", "display: none"); // Hidden by default
    this.element.appendChild(dataResults);
    */


    // Function to clear button selection
    function clearButtonSelection() {
      let i
      let tabs = document.getElementsByClassName("mela-btn")
      for (i = 0; i < tabs.length; i++) {
        tabs[i].classList.remove("selected");
      }
    }

    // Function for hiding tabs
    function hideTabs() {
      let i
      let tabs = document.getElementsByClassName("mela-tab")
      for (i = 0; i < tabs.length; i++) {
        tabs[i].setAttribute("style", "display: none");
      }
    }

    // Add event listeners
    parseButton.addEventListener('click', function () {
      clearButtonSelection();
      parseButton.classList.add("selected");
      hideTabs();
      compilationTab.removeAttribute("style")
    });
    analysisButton.addEventListener('click', function () {
      clearButtonSelection();
      analysisButton.classList.add("selected");
      hideTabs();
      analysisTab.removeAttribute("style")
    });
    simulationButton.addEventListener('click', function () {
      clearButtonSelection();
      simulationButton.classList.add("selected");
      hideTabs();
      simulationTab.removeAttribute("style")
    });

    inputSimButton.addEventListener('click', async function () {
      console.log("Clicked on input path");
      var remote = require('remote');
      var dialog = remote.require('electron').dialog;
      var path = await dialog.showOpenDialog({
        properties: ['openDirectory']
      });
      console.log(path.filePaths[0])
      if (path.filePaths[0]) {
        inputSimPathVar = path.filePaths[0];
        inputSimPath.innerHTML = path.filePaths[0];
      }
    });

    outputSimButton.addEventListener('click', async function () {
      console.log("Clicked on input path");
      var remote = require('remote');
      var dialog = remote.require('electron').dialog;
      var path = await dialog.showOpenDialog({
        properties: ['openDirectory']
      });
      if (path.filePaths[0]) {
        outputSimPathVar = path.filePaths[0];
        outputSimPath.innerHTML = path.filePaths[0];
      }
    });

    postProcessSimButton.addEventListener('click', async function () {
      console.log("Clicked on input path");
      var remote = require('remote');
      var dialog = remote.require('electron').dialog;
      var path = await dialog.showOpenDialog({
        properties: ['openFile']
      });
      if (path.filePaths[0]) {
        postProcessSimPathVar = path.filePaths[0];
        postProcessSimPath.innerHTML = path.filePaths[0];
      }
    });

    // Run simulation on click
    var simulationRunningFlag = 0;
    runSimButton.addEventListener('click', function () {
      // Run a simulation only if it is not already running
      if (!simulationRunningFlag) {
        simulationRunningFlag = 1;
        compilAndRun(melaFilePath, postProcessSimPathVar);
      }
    });

    // Define Mela var path
    var melaFilePath = "";
    var inputSimPathVar = "";
    var outputSimPathVar = "";
    var postProcessSimPathVar = "";

    // Check opened window and if it is .mela file, parse the file and compute analysis
    this.subscriptions = atom.workspace.getCenter().observeActivePaneItem(item => {
      // Display a message if no text editor is selected
      /*
      function displayMessage() {
        cmakeDiv.innerText = 'Open a .mela file to view analysis results.';
        let i
        let tabs = document.getElementsByClassName("results")
        for (i = 0; i < tabs.length; i++) {
          tabs[i].innerText = 'Open a .mela file to view analysis results.';
        }
      }
      */

      if (!atom.workspace.isTextEditor(item)) {
        //displayMessage()
        return;
      }

      // Display a message if the file is not a .mela
      if (!item.getBuffer().getPath().endsWith(".mela")) { //!
        //displayMessage();
        return;
      }

      // Get mela file path
      melaFilePath = item.getBuffer().getPath()

      const path = require('path');
      var melaDirPath = path.dirname(melaFilePath)
      //console.log("Change mela file path: " + melaFilePath)
      //console.log("Change mela file dir: " + melaDirPath)
      inputSimPathVar = path.join(melaDirPath, "simulation/input")
      outputSimPathVar = path.join(melaDirPath, "simulation/output")
      postProcessSimPathVar = path.join(melaDirPath, "simulation/postProcessing.sh")
      inputSimPath.innerHTML = inputSimPathVar
      outputSimPath.innerHTML = outputSimPathVar
      postProcessSimPath.innerHTML = postProcessSimPathVar

      // Change current dir to compilation path
      let compilePath = path.join(__dirname, "..", "mela-compiler");
      let process = require('process');
      process.chdir(compilePath);

      // Update results if a .mela file is opened
      //item.save()
      parseAndAnalysis(melaFilePath)
      //computeAnalysis(melaFilePath)

      // Update results if a .mela file is selected
      // onDidStopChanging
      this.subscriptions = item.onDidStopChanging(item2 => {
        //item.saveAs("temp.mela")
        //parseAndAnalysis("./temp.mela")
        item.save()
        parseAndAnalysis(melaFilePath)
      });
    });

    function compilAndRun(melaFilePath, postProcessSimPath) {
      if (document.getElementById("postprocesscheckbox").checked == true) {
        postProcessDiv.removeAttribute("style");
      } else {
        postProcessDiv.setAttribute("style", "display: none");
      }

      cmakeDiv.innerHTML = "Run command \"cmake\":</br>"
      cmakeDiv.innerHTML += "<span class='loading loading-spinner-tiny inline-block'></span>";
      makeDiv.innerHTML = "</br>Run command \"make\":</br>"
      makeDiv.innerHTML += "<span class='loading loading-spinner-tiny inline-block'></span>";
      simDiv.innerHTML = "</br>Run simulation:</br>"
      simDiv.innerHTML += "<span class='loading loading-spinner-tiny inline-block'></span>";
      postProcessDiv.innerHTML = "</br>Run post-processing:</br>"
      postProcessDiv.innerHTML += "<span class='loading loading-spinner-tiny inline-block'></span>";

      javaCompilation(melaFilePath, postProcessSimPath)
    }

    function javaCompilation(melaFilePath, postProcessSimPath) {

      const {exec} = require("child_process");
      
      var generate_option = "generate"
      if (document.getElementById("generateoptioncheckbox").checked == true) {
        generate_option = ""
      }
      console.log("java -jar mela-compiler.jar " + " " + melaFilePath + " " + generate_option)
      exec("java -jar mela-compiler.jar " + " " + melaFilePath + " " + generate_option, (error, stdout, stderr) => {
        javacCompilPanelInset.innerHTML = "Parse Mela application:</br>"
        if (error) {
          javacCompilPanelInset.innerHTML += "<span class='inline-block highlight-error'>Error</span>"
          javacCompilPanelInset.innerHTML += "<div class='text-error'>" + error.message.toString() + "</div>";
          parseButton.classList.add("btn-error");
        } else if (stderr) {
          javacCompilPanelInset.innerHTML += "<span class='inline-block highlight-error'>Error</span>"
          javacCompilPanelInset.innerHTML += "<div class='text-error'>" + stderr.toString() + "</div>";
          parseButton.classList.add("btn-error");
        } else {
          javacCompilPanelInset.innerHTML += "<span class='inline-block highlight-success'>Success</span>";
          parseButton.classList.remove("btn-error");
          cmakeCompilation(melaFilePath, postProcessSimPath)
        }
        if (error || stderr) {
          cmakeDiv.innerHTML = "Run command \"cmake\":</br>"
          cmakeDiv.innerHTML += "<span class='inline-block highlight-error'>Error</span>"
          makeDiv.innerHTML = "</br>Run command \"make\":</br>"
          makeDiv.innerHTML += "<span class='inline-block highlight-error'>Error</span>"
          simDiv.innerHTML = "</br>Run simulation:</br>"
          simDiv.innerHTML += "<span class='inline-block highlight-error'>Error</span>"
          postProcessDiv.innerHTML = "</br>Run post-processing:</br>"
          postProcessDiv.innerHTML += "<span class='inline-block highlight-error'>Error</span>";
          simulationRunningFlag = 0;
        }
      })
    }


    // Compile generated C code (call cmake first)
    function cmakeCompilation(melaFilePath, postProcessSimPath) {

      const {exec} = require("child_process");
      exec("cmake CMakeLists.txt", (error, stdout, stderr) => {
        cmakeDiv.innerHTML = "Run command \"cmake\":</br>"
        if (error) {
          console.log(`error: ${error.message}`);
          cmakeDiv.innerHTML += "<span class='inline-block highlight-error'>Error</span></br>"
          cmakeDiv.innerHTML += "<div class='text-error'>" + error.message.toString() + "</div>";
          simulationButton.classList.add("btn-error");
        } else if (stderr) {
          console.log(`stderr: ${stderr}`);
          cmakeDiv.innerHTML += "<span class='inline-block highlight-error'>Error</span>"
          cmakeDiv.innerHTML += "<div class='text-error'>" + stderr.toString() + "</div>";
          simulationButton.classList.add("btn-error");
        } else {
          cmakeDiv.innerHTML += "<span class='inline-block highlight-success'>Success</span>";
          //simulationCompilPanelInset.innerHTML += stdout.toString() + "</br>";
          simulationButton.classList.remove("btn-error");
          makeCompilation(melaFilePath, postProcessSimPath)
        }
        if (error || stderr) {
          makeDiv.innerHTML = "</br>Run command \"make\":</br>"
          makeDiv.innerHTML += "<span class='inline-block highlight-error'>Error</span>"
          simDiv.innerHTML = "</br>Run simulation:</br>"
          simDiv.innerHTML += "<span class='inline-block highlight-error'>Error</span>"
          postProcessDiv.innerHTML = "</br>Run post-processing:</br>"
          postProcessDiv.innerHTML += "<span class='inline-block highlight-error'>Error</span>";
          simulationRunningFlag = 0;
        }
      });
    }

    // Compile generated C code (call make second)
    function makeCompilation(melaFilePath, postProcessSimPath) {

      const {exec} = require("child_process");

      exec("make -f Makefile", (error, stdout, stderr) => {
        makeDiv.innerHTML = "</br>Run command \"make\":</br>"
        if (error) {
          console.log(`error: ${error.message}`);
          makeDiv.innerHTML += "<span class='inline-block highlight-error'>Error</span>"
          makeDiv.innerHTML += "<div class='text-error'>" + error.message.toString() + "</div>";
          simulationButton.classList.add("btn-error");
        } else if (stderr) {
          console.log(`stderr: ${stderr}`);
          makeDiv.innerHTML += "<span class='inline-block highlight-error'>Error</span>"
          makeDiv.innerHTML += "<div class='text-error'>" + stderr.toString() + "</div>";
          simulationButton.classList.add("btn-error");
        } else {
          makeDiv.innerHTML += "<span class='inline-block highlight-success'>Success</span>";
          //simulationCompilPanelInset.innerHTML += stdout.toString() + "</br>";
          simulationButton.classList.remove("btn-error");
          runSimulation(melaFilePath, postProcessSimPath);
        }
        if (error || stderr) {
          simDiv.innerHTML = "</br>Run simulation:</br>"
          simDiv.innerHTML += "<span class='inline-block highlight-error'>Error</span>"
          postProcessDiv.innerHTML = "</br>Run post-processing:</br>"
          postProcessDiv.innerHTML += "<span class='inline-block highlight-error'>Error</span>";
          simulationRunningFlag = 0;
        }
      })
    }

    function runSimulation(melaFilePath, postProcessSimPath) {

      const {exec} = require("child_process");

      //console.log("./main " + inputSimPathVar + " " + outputSimPath.innerHTML);
      exec("./main " + inputSimPathVar + " " + outputSimPathVar, (error, stdout, stderr) => {
        simDiv.innerHTML = "</br>Run simulation:</br>"
        if (error) {
          console.log(`error: ${error.message}`);
          simDiv.innerHTML += "<span class='inline-block highlight-error'>Error</span>"
          simDiv.innerHTML += "<div class='text-error'>" + error.message.toString() + "</div>";
          simulationButton.classList.add("btn-error");
        } else if (stderr) {
          console.log(`stderr: ${stderr}`);
          simDiv.innerHTML += "<span class='inline-block highlight-error'>Error</span>"
          simDiv.innerHTML += "<div class='text-error'>" + stderr.toString() + "</div>";
          simulationButton.classList.add("btn-error");
        } else {
          simDiv.innerHTML += "<span class='inline-block highlight-success'>Success</span>";
          //simulationCompilPanelInset.innerHTML += stdout.toString() + "</br>";
          simulationButton.classList.remove("btn-error");
          if (document.getElementById("postprocesscheckbox").checked == true) {
            runPostProcessing(melaFilePath, postProcessSimPath)
          }
        }
        if (error || stderr) {
          postProcessDiv.innerHTML = "</br>Run post-processing:</br>"
          postProcessDiv.innerHTML += "<span class='inline-block highlight-error'>Error</span>";
          simulationRunningFlag = 0;
        }
      })
    }

    function runPostProcessing(melaFilePath, postProcessSimPath) {

      const path = require('path');
      var simDir = path.dirname(postProcessSimPath);
      var simFile = path.basename(postProcessSimPath);

      const process = require('process');
      var currentDir = process.cwd()
      process.chdir(simDir);

      const {exec} = require("child_process");
      exec("./" + simFile, (error, stdout, stderr) => {
        postProcessDiv.innerHTML = "</br>Run post-processing:</br>"
        if (error) {
          console.log(`error: ${error.message}`);
          postProcessDiv.innerHTML += "<span class='inline-block highlight-error'>Error</span>"
          postProcessDiv.innerHTML += "<div class='text-error'>" + error.message.toString() + "</div>";
          simulationButton.classList.add("btn-error");
        } else if (stderr) {
          console.log(`stderr: ${stderr}`);
          postProcessDiv.innerHTML += "<span class='inline-block highlight-error'>Error</span>"
          postProcessDiv.innerHTML += "<div class='text-error'>" + stderr.toString() + "</div>";
          simulationButton.classList.add("btn-error");
        } else {
          postProcessDiv.innerHTML += "<span class='inline-block highlight-success'>Success</span>";
          postProcessDiv.innerHTML += "</br></br>" + stdout.toString();
          simulationButton.classList.remove("btn-error");
        }
        process.chdir(currentDir);
        simulationRunningFlag = 0;
      })
    }


    // Parse Mela and compute analysis results
    function parseAndAnalysis(melaFilePath) {

      const {exec} = require("child_process");

      console.log("java -jar mela-compiler.jar " +  " " + melaFilePath)
      let result = exec("java -jar mela-compiler.jar " +  " " + melaFilePath, (error, stdout, stderr) => {
        javacCompilPanelInset.innerHTML = "Parse Mela application:</br>"
        if (error) {
          console.log(`error: ${error.message}`);
          javacCompilPanelInset.innerHTML += "<span class='inline-block highlight-error'>Error</span>"
          javacCompilPanelInset.innerHTML += "<div class='text-error'>" + error.message.toString() + "</div>";
          parseButton.classList.add("btn-error");
        } else if (stderr) {
          console.log(`stderr: ${stderr}`);
          javacCompilPanelInset.innerHTML += "<span class='inline-block highlight-error'>Error</span>"
          javacCompilPanelInset.innerHTML += "<div class='text-error'>" + stderr.toString() + "</div>";
          parseButton.classList.add("btn-error");
        } else {
          javacCompilPanelInset.innerHTML += "<span class='inline-block highlight-success'>Success</span>";
          parseButton.classList.remove("btn-error");
        }
        showAnalysisResults();
      });
    }

    function showAnalysisResults () {

      // Global error for the Analysis button
      var globalError = false;
      var globalWarning = false;

      /*
      * processor analysis tables
      */

      const fs = require('fs');
      let rawjson = fs.readFileSync('generated/analysis/schedulingAnalysis.json');
      let sched = JSON.parse(rawjson);


      panelsHeading[0].innerHTML = "<span class='icon icon-clock'></span>"
      
      
      // First table: Mean processor usage

      panelsBody[0].innerHTML = "<b>Mean processor utilisation rate:</b>"

      // First table
      table = document.createElement("table")

      line = document.createElement("tr");
      col = document.createElement("th");
      col.textContent = "Mission step";
      line.appendChild(col);

      col = document.createElement("th");
      col.textContent = "Acquisition mode";
      line.appendChild(col);

      col = document.createElement("th");
      col.textContent = "Utilisation rate (%)";
      line.appendChild(col);

      col = document.createElement("th");
      col.textContent = "Maximum (%) ";

      line.appendChild(col);

      table.appendChild(line);


      // Add each lines of the table
      var schedulingError = false;
      sched.forEach((missionStep, i) => {
       var rowspan = missionStep.schedulingDetails.length

       line = document.createElement("tr");

       col = document.createElement("td");
       col.setAttribute("rowspan", rowspan);
       col.textContent = missionStep.missionStepName;
       line.appendChild(col);

       col = document.createElement("td");
       col.textContent = missionStep.schedulingDetails[0].acqModeName;
       line.appendChild(col);

       col = document.createElement("td");
       col.textContent = Math.round(missionStep.schedulingDetails[0].cpuUseMean*10)/10;
       line.appendChild(col);

       col = document.createElement("td");
       col.setAttribute("rowspan", rowspan);
       col.textContent = Math.round(missionStep.cpuBound*10)/10;
       line.appendChild(col);

       table.appendChild(line);

       for(let i = 1; i < missionStep.schedulingDetails.length; i++) {
          line = document.createElement("tr");

          col = document.createElement("td");
          col.textContent = missionStep.schedulingDetails[i].acqModeName;
          line.appendChild(col);

          col = document.createElement("td");
          col.textContent = Math.round(missionStep.schedulingDetails[i].cpuUseMean*10)/10;
          line.appendChild(col);

          table.appendChild(line);
       }
      });
      panelsBody[0].appendChild(table);




      // Second table: Worst-case processor usage
      
      panelsBody[0].innerHTML += "</br><b>Worst-case processor utilisation rate:</b>"

      
      table = document.createElement("table")

      line = document.createElement("tr");
      col = document.createElement("th");
      col.textContent = "Mission step";
      line.appendChild(col);

      col = document.createElement("th");
      col.textContent = "Acquisition mode";
      line.appendChild(col);

      col = document.createElement("th");
      col.textContent = "Utilisation rate (%)";
      line.appendChild(col);

      col = document.createElement("th");
      col.textContent = "Maximum (%) ";
      //info = document.createElement("span");
      //info.setAttribute("class", "icon icon-info")
      //tooltipsSubscriptions.add(atom.tooltips.add(info, {title: 'Maxium utilisation rate allowed for the processor'}));
      //col.appendChild(info)
      line.appendChild(col);

      table.appendChild(line);

      // Add each lines of the table
      var schedulingError = false;
      sched.forEach((missionStep, i) => {
        var rowspan = missionStep.schedulingDetails.length

        var classError = "";
        if(missionStep.schedulingError) {
          classError = "mela-table-text-error";
          schedulingError = true;
        } else {
          classError = "mela-table-text-success";
        }

        line = document.createElement("tr");

        col = document.createElement("td");
        col.classList.add(classError);
        col.setAttribute("rowspan", rowspan);
        col.textContent = missionStep.missionStepName;
        line.appendChild(col);

        col = document.createElement("td");
        col.classList.add(classError);
        col.textContent = missionStep.schedulingDetails[0].acqModeName;
        line.appendChild(col);

        col = document.createElement("td");
        col.classList.add(classError);
        col.textContent = Math.round(missionStep.schedulingDetails[0].cpuUseWorstCase*10)/10;
        line.appendChild(col);

        col = document.createElement("td");
        col.classList.add(classError);
        col.setAttribute("rowspan", rowspan);
        col.textContent = Math.round(missionStep.cpuBound*10)/10;
        line.appendChild(col);

        table.appendChild(line);

        for(let i = 1; i < missionStep.schedulingDetails.length; i++) {
          line = document.createElement("tr");

          col = document.createElement("td");
          col.classList.add(classError);
          col.textContent = missionStep.schedulingDetails[i].acqModeName;
          line.appendChild(col);

          col = document.createElement("td");
          col.classList.add(classError);
          col.textContent = Math.round(missionStep.schedulingDetails[i].cpuUseWorstCase*10)/10;
          line.appendChild(col);

          table.appendChild(line);
        }
      });
      if(schedulingError) {
        panelsHeading[0].innerHTML += "<span class='inline-block highlight-error'>Error</span>"
        globalError = true;
      } else {
        panelsHeading[0].innerHTML += "<span class='inline-block highlight-success'>Success</span>"
      }
      panelsBody[0].appendChild(table);


      // Second table
      panelsBody[0].innerHTML += "</br><b>Worst-case execution time:</b>"

      table = document.createElement("table")

      line = document.createElement("tr");

      col = document.createElement("th");
      col.textContent = "Mission step";
      line.appendChild(col);

      col = document.createElement("th");
      col.textContent = "Acquisition mode";
      line.appendChild(col);

      col = document.createElement("th");
      col.innerHTML = "WCET (ms) ";
      //info = document.createElement("span");
      //info.setAttribute("class", "icon icon-info")
      //tooltipsSubscriptions.add(atom.tooltips.add(info, {title: 'The Worst Case Execution Time is the longest execution time of the main sequence (the first one after the Variables)'}));
      //col.appendChild(info)
      line.appendChild(col);
      col = document.createElement("th");
      col.textContent = "Period (ms) ";
      //info = document.createElement("span");
      //info.setAttribute("class", "icon icon-info")
      //tooltipsSubscriptions.add(atom.tooltips.add(info, {title: 'The period is the time interval between each execution of the main sequence (the first one after the Variables)'}));
      //col.appendChild(info)
      line.appendChild(col);
      table.appendChild(line);

      // Add each lines of the table
      sched.forEach((missionStep, i) => {
        var rowspan = missionStep.schedulingDetails.length
        //console.log(missionStep.schedulingError)

        var classError = "";
        if(missionStep.schedulingError) {
          classError = "mela-table-text-error";
        } else {
          classError = "mela-table-text-success";
        }

        line = document.createElement("tr");

        col = document.createElement("td");
        col.classList.add(classError);
        col.setAttribute("rowspan", rowspan);
        col.textContent = missionStep.missionStepName;
        line.appendChild(col);

        col = document.createElement("td");
        col.classList.add(classError);
        col.textContent = missionStep.schedulingDetails[0].acqModeName;
        line.appendChild(col);

        col = document.createElement("td");
        col.classList.add(classError);
        col.textContent = Math.round(missionStep.schedulingDetails[0].wcet)/1000;
        line.appendChild(col);

        col = document.createElement("td");
        col.classList.add(classError);
        col.textContent = Math.round(missionStep.schedulingDetails[0].execPeriod)/1000;
        line.appendChild(col);

        table.appendChild(line);

        for(let i = 1; i < missionStep.schedulingDetails.length; i++) {
          line = document.createElement("tr");

          col = document.createElement("td");
          col.classList.add(classError);
          col.textContent = missionStep.schedulingDetails[i].acqModeName;
          line.appendChild(col);

          col = document.createElement("td");
          col.classList.add(classError);
          col.textContent = Math.round(missionStep.schedulingDetails[i].wcet)/1000;
          line.appendChild(col);

          col = document.createElement("td");
          col.classList.add(classError);
          col.textContent = Math.round(missionStep.schedulingDetails[i].execPeriod)/1000;
          line.appendChild(col);

          table.appendChild(line);
        }

      });
      panelsBody[0].appendChild(table);



      


      /*
      * Energy analysis table
      */
      rawjson = fs.readFileSync('generated/analysis/energyAnalysis.json');
      energy = JSON.parse(rawjson);

      panelsHeading[1].innerHTML = "<span class='icon icon-plug'></span>"

      if(energy.energyError) {
        classError = "text-error";
        panelsHeading[1].innerHTML += "<span class='inline-block highlight-error'>Error</span>";
        globalError = true;
      } else if(energy.energyWarning) {
        classError = "text-warning";
        panelsHeading[1].innerHTML += "<span class='inline-block highlight-warning'>Warning</span>";
        globalWarning = true;
      } else {
        classError = "text-success";
        analysisButton.classList.remove("btn-error");
        analysisButton.classList.remove("btn-warning");
        panelsHeading[1].innerHTML += "<span class='inline-block highlight-success'>Success</span>";
      }

      panelsBody[1].innerHTML = "<b>Autonomy:</b></br>"
      resume = document.createElement("div")
      resume.classList.add(classError)
      resume.innerHTML += "<b>" + Math.round(energy.autonomyCycles*10)/10 + " cycles</b></br>";
      resume.innerHTML += "<b>" + Math.round(energy.autonomyHours/24/365*10)/10 + " years</b></br>";
      panelsBody[1].appendChild(resume);
      panelsBody[1].innerHTML += "</br><b>Energy consumption rate:</b></br>";


      table = document.createElement("table")

      line = document.createElement("tr");
      col = document.createElement("th");
      col.textContent = "Mission step";
      line.appendChild(col);
      col = document.createElement("th");
      col.textContent = "Processor (%)";
      line.appendChild(col);
      col = document.createElement("th");
      col.textContent = "Sensors (%)";
      line.appendChild(col);
      //col = document.createElement("th");
      //col.textContent = "Recording (%)";
      //line.appendChild(col);
      col = document.createElement("th");
      col.textContent = "Transmission (%)";
      line.appendChild(col);
      col = document.createElement("th");
      col.textContent = "Actuators (%)";
      line.appendChild(col);
      table.appendChild(line);

      // Add each lines of the table
      energy.energyConsumptionDetails.forEach((missionStep, i) => {
        line = document.createElement("tr");

        col = document.createElement("td");
        col.textContent = missionStep.missionStepName;
        line.appendChild(col);

        col = document.createElement("td");
        col.textContent = Math.round(missionStep.processorEnergy*10)/10;
        line.appendChild(col);
        
        col = document.createElement("td");
        col.textContent = Math.round(missionStep.sensorEnergy*10)/10;
        line.appendChild(col);
        
        //col = document.createElement("td");
        //col.textContent = Math.round(missionStep.sdCardEnergy*10)/10;
        //line.appendChild(col);
        
        col = document.createElement("td");
        col.textContent = Math.round(missionStep.transmissionEnergy*10)/10;
        line.appendChild(col);

        col = document.createElement("td");
        col.textContent = Math.round(missionStep.actuatorEnergy*10)/10;
        line.appendChild(col);

        table.appendChild(line);
      });
      panelsBody[1].appendChild(table);


      /*
      * Satellite transmission analysis
      */

      rawjson = fs.readFileSync('generated/analysis/transmissionAnalysis.json');
      transmission = JSON.parse(rawjson);

      panelsHeading[2].innerHTML = "<span class='icon icon-radio-tower'></span>"

      if(transmission.transmissionError) {
        classError = "text-error";
        panelsHeading[2].innerHTML += "<span class='inline-block highlight-error'>Error</span>";
        globalError = true;
      } else if(transmission.transmissionWarning) {
        classError = "text-warning";
        panelsHeading[2].innerHTML += "<span class='inline-block highlight-warning'>Warning</span>";
        globalWarning = true;
      } else {
        classError = "text-success";
        //analysisButton.classList.remove("btn-error");
        //analysisButton.classList.remove("btn-warning");
        panelsHeading[2].innerHTML += "<span class='inline-block highlight-success'>Success</span>";
      }

      panelsBody[2].innerHTML = "<b>Satellite transmission:</b></br>"
      resume = document.createElement("div")
      resume.classList.add(classError)
      resume.innerHTML += "<b>" + Math.round(transmission.transmissionSizePerCycle*10)/10 + " kB/cycle</b></br>";
      resume.innerHTML += "<b>" + Math.round(transmission.transmissionSizePerMonth*10)/10 + " kB/month</b></br>";
      resume.innerHTML += "<b>" + Math.round(transmission.transmissionCostPerMonth*10)/10 + " euros/month</b></br>";
      panelsBody[2].appendChild(resume);
      
      /* Details of transmission table 
      panelsBody[2].innerHTML += "</br><b>Transmission details per mission step:</b></br>";

      table = document.createElement("table")

      line = document.createElement("tr");
      col = document.createElement("th");
      col.textContent = "Mission step";
      line.appendChild(col);
      col = document.createElement("th");
      col.textContent = "Transmission (kB)";
      line.appendChild(col);
      table.appendChild(line);

      // Add each lines of the table
      transmission.transmissionDetails.forEach((missionStep, i) => {
        line = document.createElement("tr");

        col = document.createElement("td");
        col.textContent = missionStep.missionStepName;
        line.appendChild(col);

        col = document.createElement("td");
        col.textContent = Math.round(missionStep.transmissionSize*10)/10;
        line.appendChild(col);

        table.appendChild(line);
      });
      panelsBody[2].appendChild(table);
      */
      
      // Show error on analysis button
      analysisButton.classList.remove("btn-error");
      analysisButton.classList.remove("btn-warning");
      if(globalError) {
        analysisButton.classList.add("btn-error");
      } else if(globalWarning) {
        analysisButton.classList.add("btn-warning");
      }
    }
  }


  // Returns an object that can be retrieved when package is activated
  serialize() {
  }

  // Tear down any state and detach
  destroy() {
    this.element.remove();
    this.subscriptions.dispose();
    //tooltipsSubscriptions.dispose();
  }

  getElement() {
    return this.element;
  }

  getTitle() {
    // Used by Atom for tab text
    return 'MeLa tools';
  }

  getURI() {
    // Used by Atom to identify the view when toggling.
    return 'atom://language-mela-view';
  }

  getDefaultLocation() {
    // This location will be used if the user hasn't overridden it by dragging the item elsewhere.
    // Valid values are "left", "right", "bottom", and "center" (the default).
    return 'right';
  }

  getAllowedLocations() {
    // The locations into which the item can be moved.
    return ['left', 'right', 'bottom'];
  }

}
