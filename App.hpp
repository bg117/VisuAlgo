#pragma once

#include "AlgoVisualizer.hpp"
#include "Algorithm.hpp"

#include <gtkmm/button.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/grid.h>
#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/scale.h>
#include <gtkmm/window.h>

#include <random>

class App : public Gtk::Window {
public:
    App();

protected:
    // signal handlers
    void on_sort_button_clicked();
    void on_reset_button_clicked();
    void on_input_size_slider_value_changed();
    void on_delay_slider_value_changed();

    // child widgets
    Gtk::Box m_root;

    Gtk::Grid         m_input_panel;
    Gtk::Label        m_input_size_label;
    Gtk::Scale        m_input_size_slider;
    Gtk::Label        m_delay_label;
    Gtk::Scale        m_delay_slider;
    Gtk::Label        m_algorithm_label;
    Gtk::ComboBoxText m_algorithm_combobox;
    Gtk::Button       m_sort_button;
    Gtk::Button       m_reset_button;

    AlgoVisualizer m_histogram;

    // data
    std::vector<int> m_data;
    std::string      m_sorting_algorithm;

    std::random_device              m_rd;
    std::mt19937                    m_gen;
    std::uniform_int_distribution<> m_dis;

    bool m_is_sorting;
    Algorithm m_algo;
};
