#pragma once

#include <gtkmm/drawingarea.h>

class AlgoVisualizer : public Gtk::DrawingArea {
public:
    AlgoVisualizer();
    void             set_data(const std::vector<int> &data);
    void             set_delay(int delay);
    bool             compare(int i, int j, const char *mode);
    int *            access(int i);
    std::vector<int> access(int start, int end);
    size_t           size();
    void             validate_sorted();
    void             reset_statistics();

protected:
    // signal handlers
    bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) override;

private:
    void delay();

    // data
    std::vector<int> m_data;

    std::tuple<int, int> m_compared;
    std::vector<int>     m_accessed;

    int m_delay;

    volatile bool m_should_validate;

    int m_accesses, m_comparisons;
};
