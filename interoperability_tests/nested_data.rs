use crate::interoperability::test::{Inner, Nested};

#[allow(dead_code)]
pub fn make_nested() -> Nested {
    Nested {
        inner: Inner { a: 1, b: 2, c: 3 },
        level: 10,
        other: 20,
        value_list: vec![30, 40, 50],
        inner_array: std::array::from_fn(expected_inner_at),
        float_array: [1.5, 3.0, 4.5, 6.0, 7.5],
        last: 60,
    }
}

#[allow(dead_code)]
pub fn is_expected_nested(data: &Nested) -> bool {
    let expected = make_nested();

    data.inner.a == expected.inner.a
        && data.inner.b == expected.inner.b
        && data.inner.c == expected.inner.c
        && data.level == expected.level
        && data.other == expected.other
        && data.value_list == expected.value_list
        && data
            .inner_array
            .iter()
            .zip(expected.inner_array.iter())
            .all(|(value, expected_value)| {
                value.a == expected_value.a
                    && value.b == expected_value.b
                    && value.c == expected_value.c
            })
        && data
            .float_array
            .iter()
            .zip(expected.float_array.iter())
            .all(|(received, expected)| (*received - expected).abs() <= 1e-6)
        && data.last == expected.last
}

fn expected_inner_at(index: usize) -> Inner {
    Inner {
        a: (index + 1) as u8,
        b: (index + 1) as u32 * 10,
        c: (index + 1) as u16 * 100,
    }
}
