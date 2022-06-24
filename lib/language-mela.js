'use babel'

import LanguageMelaView from './language-mela-view';
import { CompositeDisposable, Disposable} from 'atom';
import $ from "jquery";

export default {

  subscriptions: null,

  activate (state) {
    // Events subscribed to in atom's system can be easily cleaned up with a CompositeDisposable
    this.subscriptions = new CompositeDisposable(
      // Add an opener for our view.
      atom.workspace.addOpener(uri => {
        if (uri === 'atom://language-mela-view') {
          return new LanguageMelaView();
        }
      }),

      // Register command that toggles this view
      atom.commands.add('atom-workspace', {
        'language-mela:toggle': () => this.toggle()
      }),
      
      // Destroy any ActiveEditorInfoViews when the package is deactivated.
      new Disposable(() => {
        atom.workspace.getPaneItems().forEach(item => {
          if (item instanceof LanguageMelaView) {
            item.destroy();
          }
        });
      })
    );
  },

  deactivate() {
    this.subscriptions.dispose();
    this.languageMelaView.destroy();
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
  },
};
