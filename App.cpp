#include "App.hpp"
#include "Algorithm.hpp"

#include <iostream>

App::App()
    : m_root{},
      m_input_panel{},
      m_input_size_label{ "Input Size" },
      m_input_size_slider{ Gtk::ORIENTATION_HORIZONTAL },
      m_delay_label{ "Delay (μs)" },
      m_delay_slider{ Gtk::ORIENTATION_HORIZONTAL },
      m_algorithm_label{ "Algorithm" },
      m_algorithm_combobox{},
      m_sort_button{ "Sort" },
      m_reset_button{ "Reset Data" },
      m_histogram{},
      m_data{},
      m_rd{},
      m_gen{ m_rd() },
      m_dis{ 100, 1000 },
      m_is_sorting{ false },
      m_algo{ &m_histogram }
{
    set_title("VisuAlgo");
    set_default_size(640, 480);

    m_data.resize(1000);

    m_root.set_orientation(Gtk::ORIENTATION_VERTICAL);

    // allow input panel to expand horizontally
    m_input_panel.set_hexpand(true);

    // set spacing between widgets in input panel
    m_input_panel.set_row_spacing(10);
    m_input_panel.set_column_spacing(10);

    // padding for input panel
    m_input_panel.set_margin_start(10);
    m_input_panel.set_margin_end(10);
    m_input_panel.set_margin_top(10);
    m_input_panel.set_margin_bottom(10);

    // input: slider with label for input size
    m_input_size_label.set_halign(Gtk::ALIGN_START);

    m_input_size_slider.set_value_pos(Gtk::POS_RIGHT);
    m_input_size_slider.set_range(10, 1000);  // set range of slider to 2 to 1000
    m_input_size_slider.set_value(100);       // set default value of slider to 100
    m_input_size_slider.set_increments(1, 1); // set step size of slider to 1
    m_input_size_slider.set_digits(0);        // show current value of slider
    m_input_size_slider.set_draw_value(true); // show current value of slider
    m_input_size_slider.set_hexpand(true);    // allow slider to expand horizontally
    m_input_size_slider.signal_value_changed().connect(mem_fun(*this, &App::on_input_size_slider_value_changed));

    // input: slider with label for delay
    m_delay_label.set_halign(Gtk::ALIGN_START);

    m_delay_slider.set_value_pos(Gtk::POS_RIGHT);
    m_delay_slider.set_range(0,
                             500000);       // set range of slider to 0 to 10000 microseconds
    m_delay_slider.set_value(10000);        // 100 microseconds
    m_delay_slider.set_increments(1, 1000); // set step size of slider to 1
    m_delay_slider.set_digits(0);           // show current value of slider
    m_delay_slider.set_draw_value(true);    // show current value of slider
    m_delay_slider.set_hexpand(true);       // allow slider to expand horizontally
    m_delay_slider.signal_value_changed().connect(mem_fun(*this, &App::on_delay_slider_value_changed));

    // input: combobox for selecting algorithm
    m_algorithm_label.set_halign(Gtk::ALIGN_START);
    m_algorithm_combobox.append("Bubble Sort");
    m_algorithm_combobox.append("Selection Sort");
    m_algorithm_combobox.append("Insertion Sort");
    m_algorithm_combobox.append("Merge Sort");
    m_algorithm_combobox.append("Quick Sort");
    m_algorithm_combobox.append("Heap Sort");
    m_algorithm_combobox.set_active(0);

    // input: button for running algorithm
    m_sort_button.set_halign(Gtk::ALIGN_END);
    m_sort_button.set_hexpand(false);
    m_sort_button.signal_clicked().connect(mem_fun(*this, &App::on_sort_button_clicked));
    // show icon
    m_sort_button.set_image_from_icon_name("media-playback-start", Gtk::ICON_SIZE_BUTTON);

    // input: button for regenerating input
    m_reset_button.set_hexpand(false);
    m_reset_button.signal_clicked().connect(mem_fun(*this, &App::on_reset_button_clicked));

    // attach input widgets to input panel
    m_input_panel.attach(m_input_size_label, 0, 0, 1, 1);
    m_input_panel.attach(m_input_size_slider, 1, 0, 2, 1);
    m_input_panel.attach(m_delay_label, 0, 1, 1, 1);
    m_input_panel.attach(m_delay_slider, 1, 1, 2, 1);
    m_input_panel.attach(m_algorithm_label, 0, 2, 1, 1);
    m_input_panel.attach(m_algorithm_combobox, 1, 2, 1, 1);
    m_input_panel.attach(m_sort_button, 2, 2, 1, 1);
    m_input_panel.attach(m_reset_button, 0, 3, 1, 1);

    // 1000 random numbers between 0 and 1000
    std::generate(m_data.begin(), m_data.end(), [&]() { return m_dis(m_gen); });

    // set histogram data
    m_histogram.set_data(std::vector<int>(m_data.begin(), m_data.begin() + 100));
    m_histogram.set_hexpand(true);
    m_histogram.set_vexpand(true);

    // attach input panel and histogram to root
    m_root.add(m_input_panel);
    m_root.add(m_histogram);

    // attach input and output panels to root
    add(m_root);

    show_all();
}

void App::on_sort_button_clicked()
{
    m_histogram.reset_statistics();

    auto toggle_sorting = [&]() {
        m_is_sorting = !m_is_sorting;
        if (m_is_sorting) {
            m_sort_button.set_sensitive(false);
            m_reset_button.set_sensitive(false);
            // also disable input size slider
            m_input_size_slider.set_sensitive(false);
        }
        else {
            m_sort_button.set_sensitive(true);
            m_reset_button.set_sensitive(true);
            // also enable input size slider
            m_input_size_slider.set_sensitive(true);
        }
    };

    toggle_sorting();

    // get selected algorithm
    auto      algorithm = m_algorithm_combobox.get_active_row_number();
    Algorithm alg{ &m_histogram };

    switch (algorithm) {
    case 0: alg.bubble_sort(); break;
    case 1: alg.selection_sort(); break;
    case 2: alg.insertion_sort(); break;
    case 3: alg.merge_sort(); break;
    case 4: alg.quick_sort(); break;
    case 5: alg.heap_sort(); break;
    case 6: alg.counting_sort(); break;
    case 7: alg.radix_sort(); break;
    default: std::cout << "Invalid algorithm" << std::endl; break;
    }

    toggle_sorting();
}

void App::on_reset_button_clicked()
{
    m_histogram.reset_statistics();
    // regenerate input data
    std::generate(m_data.begin(), m_data.end(), [&]() { return m_dis(m_gen); });

    // only set from 0 to m_input_size_slider.get_value()
    m_histogram.set_data(std::vector<int>(m_data.begin(), m_data.begin() + m_input_size_slider.get_value()));
}

void App::on_input_size_slider_value_changed()
{
    m_histogram.set_data(std::vector<int>(m_data.begin(), m_data.begin() + m_input_size_slider.get_value()));
}

void App::on_delay_slider_value_changed()
{
    m_histogram.set_delay(m_delay_slider.get_value());
}
