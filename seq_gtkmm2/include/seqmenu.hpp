#ifndef SEQ64_SEQMENU_HPP
#define SEQ64_SEQMENU_HPP

/*
 *  This file is part of seq24/sequencer64.
 *
 *  seq24 is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  seq24 is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with seq24; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/**
 * \file          seqmenu.hpp
 *
 *  This module declares/defines the class that handles the right-click
 *  menu of the sequence slots in the pattern window.
 *
 * \library       sequencer64 application
 * \author        Seq24 team; modifications by Chris Ahlstrom
 * \date          2015-07-24
 * \updates       2016-05-09
 * \license       GNU GPLv2 or above
 *
 *  This module is the base class for the perfnames and mainwid classes.
 */

#include "perform.hpp"
#include "sequence.hpp"

/**
 *  Try to highlight the selected pattern using black-on-cyan
 *  coloring, in addition to the red progress bar marking that already exists.
 *  Currently, it still has issues.  Moved to the perform object.
 *
 *      #define SEQ64_EDIT_SEQUENCE_HIGHLIGHT
 */

namespace Gtk
{
    class Menu;
}

namespace seq64
{

class eventedit;
class mainwid;
class seqedit;

/**
 *  This class handles the right-click menu of the sequence slots in the
 *  pattern window.
 *
 *  It is an abstract base class.
 */

class seqmenu : public virtual Glib::ObjectBase
{

private:

    Gtk::Menu * m_menu;

    /**
     *  Provides a reference to the central (non-UI) object involved in
     *  managing a song and performance.
     */

    perform & m_mainperf;

    /**
     *  Provides a reference to the mainwid to the derived classes (even for
     *  the mainwid class) in order that seqmenu be able to pass it on to the
     *  seqedit class, for better control over the handling of the display of
     *  the "current" sequence.
     */

    mainwid & m_my_mainwid;

    /**
     *  Holds a copy of data concerning a sequence, which can then be pasted
     *  into another pattern slot.
     */

    sequence m_clipboard;

    /**
     *  Points to the latest seqedit object, if created.
     *
     * \change
     *      Added by Chris on 2015-08-02 based on compiler warnings and a
     *      comment warning in the seq_edit() function.  We'll save the
     *      result of that function here, and will let valgrind tell us
     *      later if Gtkmm takes care of it.
     */

    seqedit * m_seqedit;

    /**
     *  Points to the latest eventedit object, if created.
     */

    eventedit * m_eventedit;

    /**
     *  References the current sequence by sequence number.
     */

    int m_current_seq;

#if 0       // SEQ64_EDIT_SEQUENCE_HIGHLIGHT

    /**
     *  Hold the number of the currently-in-edit sequence.  We're moving this
     *  variable into the perform class for better control of this value.
     */

    int m_edit_sequence;

#endif      // SEQ64_EDIT_SEQUENCE_HIGHLIGHT

    /**
     *  Indicates if a sequence has been created.
     *
     * \todo
     *      We need to make sure that the perform object is in control of the
     *      modification flag.
     */

    bool m_modified;

public:

    seqmenu (perform & a_p, mainwid & mymainwid);

    /**
     *  Provides a rote base-class destructor.  This is necessary in an
     *  abstraction base class.
     */

    virtual ~seqmenu ();

    /**
     * \getter m_current_seq
     *      We're changing the name, so that "seq" indicates an integer by
     *      (an imperfect) convention.
     */

    int current_seq () const
    {
        return m_current_seq;
    }

    /**
     * \getter m_modified
     */

    bool is_modified () const
    {
        return m_modified;
    }

protected:

    /**
     * \setter m_current_seq
     */

    void current_seq (int seq)
    {
        if (seq >= 0)                   /* shall we validate the upper end? */
        {
            if (seq != m_current_seq)
            {
                m_current_seq = seq;
#ifdef SEQ64_EDIT_SEQUENCE_HIGHLIGHT
                m_mainperf.set_edit_sequence(-1);  // m_edit_sequence = -1;
#endif
            }
        }
    }

#ifdef SEQ64_EDIT_SEQUENCE_HIGHLIGHT

    /**
     * \setter m_edit_sequence
     *      Pass in -1 to disable the edit-sequence number.  Now a pass-along
     *      to the perform object.
     */

    void set_edit_sequence (int seqnum)
    {
        m_mainperf.set_edit_sequence(seqnum);   // m_edit_sequence = seqnum;
    }

    /**
     * \setter m_edit_sequence
     *      Disable the edit-sequence number if it matches the parameter.
     */

    void unset_edit_sequence (int seqnum)
    {
        m_mainperf.unset_edit_sequence(seqnum);
    }

    /**
     * \getter m_edit_sequence
     *      Tests the parameter against m_edit_sequence.  Returns true
     *      if that member is not -1, and the parameter matches it.  Now a
     *      pass-along to the perform object.
     */

    bool is_edit_sequence (int seqnum) const
    {
        return m_mainperf.is_edit_sequence(seqnum);
    }

#endif  // SEQ64_EDIT_SEQUENCE_HIGHLIGHT

    /**
     * \setter m_modified
     */

    void is_modified (bool flag)
    {
        m_modified = flag;
    }

    /**
     * \getter m_mainperf.get_sequence(current_seq())
     *      This call is used many, many times, and well worth wrapping.
     */

    sequence * get_current_sequence () const
    {
        return m_mainperf.get_sequence(m_current_seq);
    }

    /**
     *  Forwards the get-sequence call to the perform object.
     */

    sequence * get_sequence (int seqnum) const
    {
        return m_mainperf.get_sequence(seqnum);
    }

    /**
     *  Forwards the is-sequence-active check to the perform object.
     */

    bool is_current_seq_active () const
    {
        return m_mainperf.is_active(current_seq());
    }

    /**
     *  Forwards the is-sequence-in-edit check to the perform object.
     */

    bool is_current_seq_in_edit () const
    {
        return m_mainperf.is_sequence_in_edit(current_seq());
    }

    /**
     *  Forwards the new-current-sequence call to the perform object.
     */

    void new_current_sequence ()
    {
        m_mainperf.new_sequence(current_seq());
    }

    /**
     *  Forwards the new-sequence call to the perform object.
     */

    void new_sequence (int seqnum)
    {
        m_mainperf.new_sequence(seqnum);
    }

    /**
     *  Forwards the delete-sequence call to the perform object.
     */

    void delete_current_sequence()
    {
        m_mainperf.delete_sequence(current_seq());
    }

    /**
     *  Forwards the sequence-playing-toggle call to the perform object.
     */

    void toggle_current_sequence()
    {
        m_mainperf.sequence_playing_toggle(current_seq());
    }

    void popup_menu ();

protected:

    void seq_edit ();
    void seq_event_edit ();

private:

    void seq_new ();
    void seq_copy ();
    void seq_cut ();
    void seq_paste ();
    void seq_clear_perf ();
    void set_bus_and_midi_channel (int a_bus, int a_ch);
    void mute_all_tracks ();

    virtual void redraw (int a_sequence) = 0;   /* pure virtual function    */

private:        // callback

    void on_realize ();

};              // class seqmenu

}               // namespace seq64

#endif          // SEQ64_SEQMENU_HPP

/*
 * seqmenu.hpp
 *
 * vim: sw=4 ts=4 wm=4 et ft=cpp
 */

