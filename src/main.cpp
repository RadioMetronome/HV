#include "gtkmm/headerbar.h"
#include "gtkmm/hvbox.h"
#include "sigc++/functors/ptr_fun.h"
#include <cstring>
#include <gtkmm.h>
#include <tuple>
#include <webkit2/webkit2.h>
#include <iostream>
/* COMPILE WITH:
*  g++ main.cc `pkg-config gtkmm-3.0 --libs --cflags` `pkg-config webkit2gtk-4.0 --libs --cflags` -std=c++17
*/
//Useless digits *cries in uselessness*
typedef struct{
  int x, y;
} vector2d;

std::string remove_useless_digits(std::string input)
{
  int pos{-1};
  for(int i{static_cast<int>(input.size())}; i >= 0; i--)
  {
      if(input[i] == ',')
      {
        pos = i;
        break;
      }
  }
  //Didn't want to reverse a string
  std::string r{""};
  for(int i{0}; i < pos; i++)
  {
    r += input[i]; 
  }
  return r;
}

void connect_to_proton()
{
  l:
    int i{system("sudo protonvpn c -f")};
    if(i != 0)
    {
      goto l;
    }
}

void go_back(WebKitWebView * webView)
{
  webkit_web_view_go_back(webView);
}
void go_forward(WebKitWebView * webView)
{
  webkit_web_view_go_forward(webView);
}

static void on_load_changed (WebKitWebView  *web_view, WebKitLoadEvent load_event, GObject * user_data)
{
  std::string progress{remove_useless_digits(std::to_string(webkit_web_view_get_estimated_load_progress(web_view) * 100)) + "%"};
  switch (load_event) {
   
    case WEBKIT_LOAD_STARTED:
          //Get ready in 5...4...3...2...1... getDeobfuscatedURL(GBQ""")
          gtk_header_bar_set_subtitle(GTK_HEADER_BAR(user_data), progress.c_str());
               
        break;
    case WEBKIT_LOAD_REDIRECTED:
          //Oh noes, I've got a virus!
          gtk_header_bar_set_subtitle(GTK_HEADER_BAR(user_data), progress.c_str());
        
        break;
    case WEBKIT_LOAD_COMMITTED:
          //Haha yes, an URL is more commited than you are 
          gtk_header_bar_set_subtitle(GTK_HEADER_BAR(user_data), progress.c_str());
        
        break;
    case WEBKIT_LOAD_FINISHED:
          //AT LEAST
          gtk_header_bar_set_subtitle(GTK_HEADER_BAR(user_data), progress.c_str());
          gtk_widget_grab_focus(GTK_WIDGET(web_view));
        break;
    }
}

//This is the ultimate ciphering and nobody can tell me it's not
std::string getDeobfuscatedURL(std::string obfuscated_url)
{
  //Viva los pointers! (I don't know shit about spanish lol)
  for(char &c : obfuscated_url)
  {
    c--; //This fucking programming language be like
  }
  return obfuscated_url;
}

std::string obfuscateURL(std::string url)
{
  for(char &C : url) //I had to do it...
  {
    C++; //Haha yes joke
  }
  return url;
}

/*  WARNING: PROFANITY
    
    Prepare to read nono words and accusations against you and Joe

    Who is Joe, you ask?

    JOE MAMA!!!!
*/

int main( int argc, char **argv)
{
  int p{0};
  vector2d dimensions{800, 600};
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create();
  Gtk::HeaderBar titlebar;
  titlebar.set_title("HV");
  std::string url{"iuuq;00svmf45/yyy"}; //I dare you

  Gtk::Button goBack, goForward; //Some basic controls for the UI not to be fucking shit
  Gtk::HBox buttonsBox;


  if(argc >= 2)
  {
    for(int i{1}; i < argc; i++){
      if(strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--protonvpn") == 0)
      {
        p = 1;
        connect_to_proton();
      }
      else if(strcmp(argv[i], "-c") == 0 || strcmp(argv[i], "--clearnet") == 0)
      {
        std::cout << "I hope you're prepared for any consequences\n";
        std::cout << "You're not running either tor nor any VPN unless you've opened it from somewhere\n";
        std::cout << "Your activity is not private. \nI'm not responsible if North Korea nukes you and/or somebody eats your cat\n";
        p = 2;
      }
      else if(strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "--oifoubj") == 0)
      {
        //I dare you
        url = "iuuq;00oifoubj/ofu";
      }
      else if(strcmp(argv[i], "-s") == 0 || strcmp(argv[i], "--size") == 0)
      {
        i++;
        dimensions.x = std::stoi(argv[i]); //I dare you to put 312947239 in here
        i++;
        dimensions.y = std::stoi(argv[i]); //I dare you
      }
      else
      {
        //Yes, you can fucking keyboard smash but webView will show a poorly translated message instead of crashing
        url = obfuscateURL(argv[i]); 
      }
    }
  }
  
  WebKitSettings * settings = WEBKIT_SETTINGS(webkit_settings_new());

  Gtk::Window window;
  window.set_default_size( dimensions.x, dimensions.y );
  window.set_titlebar(titlebar);
  titlebar.set_show_close_button();
  titlebar.set_border_width(1);

  buttonsBox.pack_start(goBack);
  buttonsBox.pack_start(goForward);

  goForward.set_image_from_icon_name("go-next-symbolic");
  goBack.set_image_from_icon_name("go-next-symbolic-rtl");
  titlebar.pack_start(buttonsBox);

  WebKitWebView * webView =  WEBKIT_WEB_VIEW( webkit_web_view_new() );
  /*
   * the next line does some tricks :
   * GTK_WIDGET( webView ) -> convert WebKitWebView to GtkWidget (webView->someting)
   * Glib::wrap( GTK_WIDGET( webView ) ) -> convert GtkWidget to Gtk::Widget (webView->webView_widget)
   */
  WebKitWebsiteDataManager * manager = webkit_web_view_get_website_data_manager(webView);

  Gtk::Widget * webView_widget = Glib::wrap( GTK_WIDGET( webView ) );

  window.add( *webView_widget );
  if(p == 0){
    WebKitNetworkProxySettings * s = webkit_network_proxy_settings_new ("socks://127.0.0.1:9050", NULL);
    webkit_website_data_manager_set_network_proxy_settings(manager, WEBKIT_NETWORK_PROXY_MODE_CUSTOM,s);
  }  
  webkit_web_view_load_uri(webView, getDeobfuscatedURL(url).c_str());

  goForward.signal_clicked().connect(sigc::bind(sigc::ptr_fun(go_forward), webView));
  goBack.signal_clicked().connect(sigc::bind(sigc::ptr_fun(go_back), webView));
  g_signal_connect_object(webView,"load-changed",G_CALLBACK(on_load_changed), titlebar.gobj(), G_CONNECT_AFTER);


  window.show_all();

  app->run( window );

  if(p == 1)
  {
    system("sudo protonvpn d");
  }

  exit( 0 );
}

