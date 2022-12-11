# Text View Widget

[`<termox/widget/widgets/text_view.hpp>`](../../../include/termox/widget/widgets/text_view.hpp)

Non-interactive box to display a given `Glyph_string`. Provides operations to
change the text, wrap words on spaces, change the alignment of the text and
scroll through the text, and others.

```cpp
class Text_view : public Widget {
   public:
    struct Parameters {
        Glyph_string text  = U"";
        Align alignment    = Align::Left;
        Wrap wrap          = Wrap::Word;
        Brush insert_brush = Brush{};
    };

    // Brush to be applied to all new incoming Glyphs, but not existing Glyphs.
    /* Widget::brush is applied after this Brush. */
    Brush insert_brush;

    // Emitted when text is scrolled up. Sends number of lines scrolled by.
    sl::Signal<void(int n)> scrolled_up;

    // Emitted when text is scrolled down. Sends number of lines scrolled by.
    sl::Signal<void(int n)> scrolled_down;

    // Emitted when text is scrolled, sends the top line.
    sl::Signal<void(int n)> scrolled_to;

    // Emitted when contents are modified. Sends a reference to the contents.
    sl::Signal<void(Glyph_string const&)> contents_modified;

    // Emitted when total line count changes.
    sl::Signal<void(int)> line_count_changed;

   public:
    // Construct a Text_view with initial Glyph_string \p text.
    /* By default, wraps text, and has left alignment. */
    Text_view(Glyph_string text  = U"",
              Align alignment    = Align::Left,
              Wrap wrap          = Wrap::Word,
              Brush insert_brush = Brush{});

    Text_view(Parameters);

   public:
    // Replace the current contents with \p text.
    /* Reset the display to show the first line at the top of the screen and
     * the cursor at the first Glyph, or where the first Glyph would be. */
    void set_text(Glyph_string text);

    // Return the entire contents of the Text_view.
    /* Provided as a non-const reference so contents can be modified without
     * limitation from the Text_view interface. Be sure to call
     * Text_view::update() after modifying the contents directly. */
    auto text() -> Glyph_string&;

    // Return the entire contents of the Text_view.
    auto text() const -> Glyph_string const&;

    // Set the Alignment, changing how the contents are displayed.
    /* Not fully implemented at the moment, Left alignment is currently
     * supported. */
    void set_alignment(Align type);

    // Return the currently used Alignment.
    auto alignment() const -> Align;

    // Set the type of text wrapping at line boundaries.
    void set_wrap(Wrap w);

    // Return the currently set text Wrap type.
    auto wrap() const -> Wrap;

    // Inserts \p text starting at \p index into the current contents.
    /* Applys insert_brush to each Glyph added. Index can be one past the
     * current length of the contents, to append. No-op if index is larger than
     * one past the current length of contents. */
    void insert(Glyph_string text, int index);

    // Inserts \p text to the end of the current contents.
    /* Applys insert_brush to each Glyph inserted. */
    void append(Glyph_string text);

    // Remove Glyphs from contents starting at \p index, for \p length Glyphs.
    void erase(int index, int length = Glyph_string::npos);

    // Remove the last Glyph from the current contents. No-op if this->empty();
    void pop_back();

    // Remove all Glyphs from the this text display.
    /* this->empty() is true after call. */
    void clear();

    // Scroll the display up by \p n lines.
    /* Tops out at the first line displayed at the top of the display. */
    virtual void scroll_up(int n = 1);

    // Scroll the display down by \p n lines.
    /* Bottoms out at the last line displaying at the top of the display. */
    virtual void scroll_down(int n = 1);

    // Return the length of the line at row \p y.
    /* Index 0 is the top of the Widget. */
    auto row_length(int y) const -> int;

    // Return the number of lines currently displayed.
    auto display_height() const -> int;

    // Return the total number of lines in display_state_.
    auto line_count() const -> int;

    // Set the top line, by row index.
    void set_top_line(int n);

    // Return the index into the contents from a physical Point on the Widget.
    /* If \p position is past any text on the corresponding line, then return
     * index of the last Glyph on that line. If Point is past displayed lines,
     * return the index of the last Glyph in contents. */
    auto index_at(Point position) const -> int;

    // Return the position of the Glyph at \p index.
    /* If \p index is not currently displayed on screen, return the closest
     * Glyph position to \p index that is displayed on screen. */
    auto display_position(int index) const -> Point;

    // Add call to Text_view::update_display() before posting Paint_event.
    void update() override;
};
```
