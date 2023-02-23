#include "color.h"

Color mix(Color c1, Color c2) {
    if (c1 == c2) return c1;
    return (Color)std::min(c1 + c2, 10);
}

Color mix(std::vector<Color>& colors) {
    if (colors.size() == 0) return WHITE;
    Color output = WHITE;
    do {
        Color curr = WHITE;
        for (Color c : colors) {
            curr = mix(curr, c);
        }
        output = (Color)std::max(output, curr);
    } while (std::next_permutation(colors.begin(), colors.end()));
    return output;
}

Color blue(Color c) {
    switch (c) {
    case 0:
        return (Color)0;
    case 3:
        return (Color)3;
    case 4:
        return (Color)4;
    case 5:
        return (Color)5;
    case 7:
        return (Color)4;
    case 8:
        return (Color)5;
    case 9:
        return (Color)5;
    case 10:
        return (Color)10;
    }
}

Color red(Color c) {
    switch (c) {
    case 0:
        return (Color)0;
    case 3:
        return (Color)3;
    case 4:
        return (Color)4;
    case 5:
        return (Color)5;
    case 7:
        return (Color)3;
    case 8:
        return (Color)3;
    case 9:
        return (Color)4;
    case 10:
        return (Color)10;
    }
}

std::string getName(Color c) {
    switch (c) {
    case 0:
        return "white";
    case 3:
        return "red";
    case 4:
        return "yellow";
    case 5:
        return "blue";
    case 7:
        return "orange";
    case 8:
        return "purple";
    case 9:
        return "green";
    case 10:
        return "trash";
    }
}
