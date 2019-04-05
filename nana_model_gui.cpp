#include <nana/gui.hpp>
#include <nana/gui/widgets/slider.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/combox.hpp>
#include  <nana/gui/timer.hpp>

class cModel;


/// The GUI class interacts with the user
class cGUI
{
public:
    /** CTOR
        @param[in] parent where GUI will be displayed
        @param[in] model reference to model we are providing user interface for
    */
    cGUI(
        nana::form& parent,
        cModel& model );

private:
    cModel& model;
    nana::form& myParent;
    nana::slider sl;
    nana::combox cb;
    nana::label status;
    nana::timer update;

    /** Start update timer

    Several times per second this updates the model
    with the current widget values.

    This saves writing a lot of code to handle
    individual widget events

    */
    void StartUpdateTimer();

    // locate widgets in display
    void move();

    // do a model update from widgets
    void OnTimer();

    void SpecifyWidgets();
};

/// Application model with two attributes alpha & beta
class cModel
{
public:

    // construct with default attribute value
    cModel()
        : myAlpha( 10 )
        , myBeta( "default ")
        , myRecalulate( false )
    {

    }

    /** do something useful when attribute values change

    This is called several times a second
    so if the recalculation takes any time at all
    it should only be done if neccessary
    */
    void Calculate()
    {
        if( ! myRecalulate )
            return;

        // ... do whatever here ...

        myRecalulate = false;

    }

    // setters
    void alpha( int v )
    {
        if( v != myAlpha )
        {
            myRecalulate = true;
            myAlpha = v;
        }
    }
    void beta( const std::string& v )
    {
        if( v != myBeta )
        {
            myRecalulate = true;
            myBeta = v;
        }
    }

    // getters
    int alpha() const
    {
        return myAlpha;
    }
    std::string beta()
    {
        return myBeta;
    }

private:
    int myAlpha;
    std::string myBeta;
    bool myRecalulate;      // true if recalculation needed
};

cGUI::cGUI(
    nana::form& parent,
    cModel& m )
    : model( m )
    , myParent( parent )
    , sl( parent )
    , cb( parent )
    , status( parent )
{
    // locate the widgets
    move();

    SpecifyWidgets();

    StartUpdateTimer();

    // handle application window resized
    myParent.events().resized([this]
    {
        move();
    });
}
void cGUI::move()
{
    // evenly space the widgets along the height of the application window
    int yinc = myParent.size().height / 4;
    int y = yinc;
    sl.move( {20, y, 200, 25 });
    y += yinc;
    cb.move( {20, y, 200, 25 });
    y += yinc;
    status.move( { 20, y, 200, 50 });
}

void cGUI::SpecifyWidgets()
{
    // specify range of 0 to 100 ( including 0 and 100 )
    // Note negative values are not supported!
    sl.maximum( 100 );

    // specify available options
    cb.push_back("item 1");
    cb.push_back("item 2");
    cb.push_back("item 3");
    cb.push_back("item 4");
}

void cGUI::StartUpdateTimer()
{
    update.interval( 300 );
    update.elapse( [this]()
    {
        OnTimer();
    });
    update.start();
}
void cGUI::OnTimer()
{
    // update model attributes
    model.alpha( sl.value() );
    model.beta( cb.caption() );

    // recalculate model
    model.Calculate();

    // display model status
    status.caption(
        "Alpha: " + std::to_string( model.alpha())
        + "\nBeta: " + model.beta() );
}
int main()
{
    // construct form for GUI
    nana::form fm;

    // construct applicartion model
    cModel model;

    // construct GUI for model
    cGUI GUI( fm, model );

    // off we go!
    fm.show();
    nana::exec();
}
