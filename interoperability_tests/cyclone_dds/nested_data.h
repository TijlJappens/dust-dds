#ifndef NESTED_DATA_H
#define NESTED_DATA_H

#include "ddsc/dds.h"
#include "NestedType.h"

#include <stdbool.h>
#include <math.h>

static inline void interoperability_test_nested_fill(interoperability_test_Nested *msg)
{
	if (msg == NULL)
	{
		return;
	}

	msg->inner.a = 1;
	msg->inner.b = 2;
	msg->inner.c = 3;
	msg->level = 10;
	msg->other = 20;
	msg->last = 60;

	msg->value_list._buffer = dds_sequence_int64_allocbuf(3);
	msg->value_list._length = 3;
	msg->value_list._release = true;
	msg->value_list._buffer[0] = 30;
	msg->value_list._buffer[1] = 40;
	msg->value_list._buffer[2] = 50;

	for (int i = 0; i < 10; i++)
	{
		msg->inner_array[i].a = (uint8_t)(i + 1);
		msg->inner_array[i].b = (uint32_t)((i + 1) * 10);
		msg->inner_array[i].c = (uint16_t)((i + 1) * 100);
	}

	for (int i = 0; i < 5; i++)
	{
		msg->float_array[i] = (float)(i + 1) * 1.5f;
	}
}

static inline bool interoperability_test_nested_is_expected(const interoperability_test_Nested *msg)
{
	if (msg == NULL)
	{
		return false;
	}

	interoperability_test_Nested expected = {0};
	interoperability_test_nested_fill(&expected);

	bool is_match = true;

	if (msg->inner.a != expected.inner.a || msg->inner.b != expected.inner.b || msg->inner.c != expected.inner.c)
	{
		is_match = false;
	}

	if (is_match && (msg->level != expected.level || msg->other != expected.other || msg->last != expected.last))
	{
		is_match = false;
	}

	if (is_match
		&& (msg->value_list._length != expected.value_list._length
			|| msg->value_list._buffer == NULL
			|| expected.value_list._buffer == NULL))
	{
		is_match = false;
	}

	if (is_match)
	{
		for (uint32_t i = 0; i < expected.value_list._length; i++)
		{
			if (msg->value_list._buffer[i] != expected.value_list._buffer[i])
			{
				is_match = false;
				break;
			}
		}
	}

	if (is_match)
	{
		for (int i = 0; i < 10; i++)
		{
			if (msg->inner_array[i].a != expected.inner_array[i].a
				|| msg->inner_array[i].b != expected.inner_array[i].b
				|| msg->inner_array[i].c != expected.inner_array[i].c)
			{
				is_match = false;
				break;
			}
		}
	}

	if (is_match)
	{
		for (int i = 0; i < 5; i++)
		{
			if (fabsf(msg->float_array[i] - expected.float_array[i]) > 1e-6f)
			{
				is_match = false;
				break;
			}
		}
	}

	if (expected.value_list._buffer != NULL)
	{
		dds_free(expected.value_list._buffer);
	}

	return is_match;
}

#endif
