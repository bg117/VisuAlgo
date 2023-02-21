#include "AlgoVisualizer.hpp"

#include <algorithm>
#include <iostream>

#include <glibmm.h>
#include <gtkmm.h>

AlgoVisualizer::AlgoVisualizer()
    : m_data{},
      m_compared{ -1, -1 },
      m_accessed{ -1 },
      m_delay{ 100 },
      m_should_validate{},
      m_accesses{},
      m_comparisons{}
{}

void AlgoVisualizer::set_data(const std::vector<int> &data)
{
    m_data = data;
    queue_draw();
}

void AlgoVisualizer::set_delay(int delay)
{
    m_delay = delay;
}

bool AlgoVisualizer::on_draw(const Cairo::RefPtr<Cairo::Context> &cr)
{
    // get width and height of widget
    int width  = get_allocated_width();
    int height = get_allocated_height() - 10; // leave space for labels

    // get max value in data (for scaling)
    int max = *std::max_element(m_data.begin(), m_data.end());

    // draw bars
    for (int i = 0; i < m_data.size(); i++) {
        // get bar height
        int bar_height = (m_data[i] / static_cast<double>(max)) * height;

        // check if bar is being compared
        if (i == std::get<0>(m_compared) || i == std::get<1>(m_compared)) {
            cr->set_source_rgb(1, 0.5, 0); // orange
        }
        // if being accessed, set color to blue
        else if (std::find(m_accessed.begin(), m_accessed.end(), i) != m_accessed.end()) {
            cr->set_source_rgb(0, 0.5, 1); // blue
        }                                  // if should validate sorted, compare with next bar and set color green
        // if less than or red if greater than (not sorted)
        else if (m_should_validate) {
            if (i < m_data.size() - 1) {
                if (m_data[i] <= m_data[i + 1]) {
                    cr->set_source_rgb(0, 1, 0); // green
                }
                else {
                    cr->set_source_rgb(1, 0, 0); // red
                    m_should_validate = false;
                }
            }
            else {
                cr->set_source_rgb(0, 1, 0); // green
            }
        }
        else {
            cr->set_source_rgb(0, 0, 0); // black
        }

        // draw bar
        cr->rectangle(i * (width / static_cast<double>(m_data.size())),
                      height - bar_height + 50,
                      width / static_cast<double>(m_data.size()),
                      bar_height);
        cr->fill();
    }

    // draw text
    cr->set_source_rgb(0, 0, 0);
    cr->set_font_size(10);
    cr->move_to(10, 10);
    cr->show_text("Accesses: " + std::to_string(m_accesses));
    cr->move_to(10, 20);
    cr->show_text("Comparisons: " + std::to_string(m_comparisons));

    return true;
}

bool AlgoVisualizer::compare(int i, int j, const char *mode)
{
    // mark bars as being compared as orange
    m_compared = std::make_tuple(i, j);

    // redraw
    queue_draw();

    // wait for delay
    delay();

    m_compared = std::make_tuple(-1, -1);

    ++m_comparisons;

    if (strcmp(mode, ">") == 0) {
        // return true if i > j
        return m_data[i] > m_data[j];
    }
    if (strcmp(mode, "<") == 0) {
        // return true if i < j
        return m_data[i] < m_data[j];
    }
    if (strcmp(mode, ">=") == 0) {
        // return true if i >= j
        return m_data[i] >= m_data[j];
    }
    if (strcmp(mode, "<=") == 0) {
        // return true if i <= j
        return m_data[i] <= m_data[j];
    }
    if (strcmp(mode, "==") == 0) {
        // return true if i == j
        return m_data[i] == m_data[j];
    }
    if (strcmp(mode, "!=") == 0) {
        // return true if i != j
        return m_data[i] != m_data[j];
    }

    return false;
}

int *AlgoVisualizer::access(int i)
{
    // mark bar as being accessed as blue
    m_accessed = { i };

    // redraw
    queue_draw();

    // wait for delay
    delay();

    m_accessed = { -1 };

    ++m_accesses;

    // return value at index i
    return &m_data[i];
}

std::vector<int> AlgoVisualizer::access(int start, int end)
{
    // mark bars as being accessed as blue
    m_accessed = std::vector<int>(m_data.begin() + start, m_data.begin() + start + end);

    // redraw
    queue_draw();

    // wait for delay
    delay();

    auto cp = m_accessed;

    m_accessed = { -1 };

    m_accesses += end - start;

    // return value at index i
    return cp;
}

size_t AlgoVisualizer::size()
{
    return m_data.size();
}

void AlgoVisualizer::delay()
{
    if (!m_delay)
        return;

    Glib::usleep(m_delay);
    while (Gtk::Main::events_pending()) {
        Gtk::Main::iteration(false);
    }
}

void AlgoVisualizer::validate_sorted()
{
    int old_delay = m_delay;
    set_delay(100000);

    m_should_validate = true;
    queue_draw();
    delay();
    m_should_validate = false;

    set_delay(old_delay);
}

void AlgoVisualizer::reset_statistics()
{
    m_accesses    = 0;
    m_comparisons = 0;

    queue_draw();
}
