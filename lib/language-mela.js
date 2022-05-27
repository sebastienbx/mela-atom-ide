'use babel'

import LanguageMelaView from './language-mela-view';
import { CompositeDisposable, Disposable} from 'atom';
import $ from "jquery";

export default {

  //languageMelaView: null,
  //modalPanel: null,
  subscriptions: null,

  activate (state) {
    /*
    this.languageMelaView = new LanguageMelaView(state.languageMelaViewState);
    this.modalPanel = atom.workspace.addRightPanel({
      item: this.languageMelaView.getElement(),
      visible: false
    });
    */

    // Events subscribed to in atom's system can be easily cleaned up with a CompositeDisposable
    this.subscriptions = new CompositeDisposable(
      // Add an opener for our view.
      atom.workspace.addOpener(uri => {
        if (uri === 'atom://language-mela-view') {
          return new LanguageMelaView();
        }
      }),

      atom.workspace.addOpener(uri => {
        if (uri === 'atom://language-mela-simulation') {
          return new LanguageMelaSimulation();
        }
      }),

      /*atom.workspace.addOpener(uri => {
        if (uri === 'atom://language-mela-plot') {
          return new LanguageMelaPlot();
        }
      }),*/

      // Register command that toggles this view
      atom.commands.add('atom-workspace', {
        'language-mela:toggle': () => this.toggle()
      }),

      // Register command that toggles this view
      /*
      atom.commands.add('atom-workspace', {
        'language-mela:plot': () => this.plot()
      }),
      */

      // Destroy any ActiveEditorInfoViews when the package is deactivated.

      new Disposable(() => {
        atom.workspace.getPaneItems().forEach(item => {
          if (item instanceof LanguageMelaView) {
            item.destroy();
          }
        });
        atom.workspace.getPaneItems().forEach(item => {
          if (item instanceof LanguageMelaSimulation) {
            item.destroy();
          }
        });
        /*atom.workspace.getPaneItems().forEach(item => {
          if (item instanceof LanguageMelaPlot) {
            item.destroy();
          }
        });*/
      })
    );
  },

  sleep(milliseconds) {
    const date = Date.now();
    let currentDate = null;
    do {
      currentDate = Date.now();
    } while (currentDate - date < milliseconds);
  },


  deactivate() {
    //this.modalPanel.destroy();
    this.subscriptions.dispose();
    //this.languageMelaView.destroy();
  },

  serialize() {
    /*
    return {
      languageMelaViewState: this.languageMelaView.serialize()
    };
    */
  },

  toggle() {
    console.log('LanguageMela was toggled!');

    atom.workspace.open('atom://language-mela-view');

    //atom.workspace.open('atom://language-mela-view');




    //$('.syntax--support.syntax--class').css('font-weight', 'bold');
    /*
    if (!this.modalPanel.isVisible()) {
      this.modalPanel.show();
    }
    */

    /*
    range = editor.getSelectedBufferRange()
    marker = editor.markBufferRange(range)
    decoration = editor.decorateMarker(marker, {type: 'line', class: 'my-line-class'})
    */




    //editor = atom.workspace.getActiveTextEditor().getElement();
    //console.log(docu);
    /*jQuery(docu).ready(function($) {

        // Votre code ici avec les appels à la fonction $()
    });*/

    //$('.syntax--support.syntax--class').css('color', 'red');


    /*
    return (
      this.modalPanel.isVisible() ?
      this.modalPanel.hide() :
      this.modalPanel.show()
    );
    */

    //atom.workspace.open('atom://language-mela-plot');

  },

  plot() {
    console.log('Create new plot 0');
    /*
    //In case only one instance of plot is needed:
    this.subscriptions.add(
      atom.workspace.addOpener(uri => {
        if (uri === 'atom://language-mela-plot') {
          return new LanguageMelaPlot();
        }
      })
    );
    */



    //var myElement=document.getElementById("plotdiv");
    //$(window).trigger('resize');
    //console.log(document);
    //console.log(myElement);
    //console.log($.find("#plotdiv"));

    //var plotview = ;
    //atom.workspace.open(new LanguageMelaPlot());

    /*
    $("#plotdiv").ready(() => {
      console.log('ready');
      this.plot();
    });
    */


    var trace1 = {
      x: [1, 2, 3, 4],
      y: [10, 15, 13, 17],
      mode: 'markers',
      type: 'scatter'
    };

    var trace2 = {
      x: [2, 3, 4, 5],
      y: [16, 5, 11, 9],
      mode: 'lines',
      type: 'scatter'
    };

    var trace3 = {
      x: [1, 2, 3, 4],
      y: [12, 9, 15, 12],
      mode: 'lines+markers',
      type: 'scatter'
    };

    var data = [trace1, trace2, trace3];

    Plotly.newPlot('plotdiv', data);

    // Open several windows



  }

};
