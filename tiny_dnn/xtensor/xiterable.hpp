/***************************************************************************
* Copyright (c) 2016, Johan Mabille, Sylvain Corlay and Wolf Vollprecht    *
*                                                                          *
* Distributed under the terms of the BSD 3-Clause License.                 *
*                                                                          *
* The full license is in the file LICENSE, distributed with this software. *
****************************************************************************/

#ifndef XITERABLE_HPP
#define XITERABLE_HPP

#include "xiterator.hpp"

namespace xt {

/*******************
 * xconst_iterable *
 *******************/

template <class D>
struct xiterable_inner_types;

#define DL DEFAULT_LAYOUT

/**
 * @class xconst_iterable
 * @brief Base class for multidimensional iterable constant expressions
 *
 * The xconst_iterable class defines the interface for multidimensional
 * constant expressions that can be iterated.
 *
 * @tparam D The derived type, i.e. the inheriting class for which
 * xconst_iterable
 *           provides the interface.
 */
template <class D>
class xconst_iterable {
 public:
  using derived_type = D;

  using iterable_types   = xiterable_inner_types<D>;
  using inner_shape_type = typename iterable_types::inner_shape_type;

  using stepper       = typename iterable_types::stepper;
  using const_stepper = typename iterable_types::const_stepper;

  template <layout_type L>
  using layout_iterator = xiterator<stepper, inner_shape_type*, L>;
  template <layout_type L>
  using const_layout_iterator = xiterator<const_stepper, inner_shape_type*, L>;
  template <layout_type L>
  using reverse_layout_iterator = std::reverse_iterator<layout_iterator<L>>;
  template <layout_type L>
  using const_reverse_layout_iterator =
    std::reverse_iterator<const_layout_iterator<L>>;

  template <class S, layout_type L>
  using broadcast_iterator = xiterator<stepper, S, L>;
  template <class S, layout_type L>
  using const_broadcast_iterator = xiterator<const_stepper, S, L>;
  template <class S, layout_type L>
  using reverse_broadcast_iterator =
    std::reverse_iterator<broadcast_iterator<S, L>>;
  template <class S, layout_type L>
  using const_reverse_broadcast_iterator =
    std::reverse_iterator<const_broadcast_iterator<S, L>>;

  using storage_iterator               = layout_iterator<DL>;
  using const_storage_iterator         = const_layout_iterator<DL>;
  using reverse_storage_iterator       = reverse_layout_iterator<DL>;
  using const_reverse_storage_iterator = const_reverse_layout_iterator<DL>;

  using iterator               = layout_iterator<DL>;
  using const_iterator         = const_layout_iterator<DL>;
  using reverse_iterator       = reverse_layout_iterator<DL>;
  using const_reverse_iterator = const_reverse_layout_iterator<DL>;

/**********************************
 * xconst_iterable implementation *
 **********************************/

/**
 * @name Constant iterators
 */
//@{
/**
 * Returns a constant iterator to the first element of the expression.
 * @tparam L layout used for the traversal. Default value is \c DEFAULT_LAYOUT.
 */

template <layout_type L = DL>
auto begin() const noexcept
  -> const_layout_iterator<L> {
  return cbegin<L>();
}

/**
 * Returns a constant iterator to the element following the last element
 * of the expression.
 * @tparam L layout used for the traversal. Default value is \c DEFAULT_LAYOUT.
 */

template <layout_type L = DL>
auto end() const noexcept
  -> const_layout_iterator<L> {
  return cend<L>();
}

/**
 * Returns a constant iterator to the first element of the expression.
 * @tparam L layout used for the traversal. Default value is \c DEFAULT_LAYOUT.
 */

template <layout_type L = DL>
auto cbegin() const noexcept
  -> const_layout_iterator<L> {
  return get_cbegin<L>(false);
}

/**
 * Returns a constant iterator to the element following the last element
 * of the expression.
 * @tparam L layout used for the traversal. Default value is \c DEFAULT_LAYOUT.
 */

template <layout_type L = DL>
auto cend() const noexcept
  -> const_layout_iterator<L> {
  return get_cend<L>(false);
}
//@}

/**
 * @name Constant reverse iterators
 */
//@{
/**
 * Returns a constant iterator to the first element of the reversed expression.
 * @tparam L layout used for the traversal. Default value is \c DEFAULT_LAYOUT.
 */

template <layout_type L = DL>
auto rbegin() const noexcept
  -> const_reverse_layout_iterator<L> {
  return crbegin<L>();
}

/**
 * Returns a constant iterator to the element following the last element
 * of the reversed expression.
 * @tparam L layout used for the traversal. Default value is \c DEFAULT_LAYOUT.
 */

template <layout_type L = DL>
auto rend() const noexcept
  -> const_reverse_layout_iterator<L> {
  return crend<L>();
}

/**
 * Returns a constant iterator to the first element of the reversed expression.
 * @tparam L layout used for the traversal. Default value is \c DEFAULT_LAYOUT.
 */

template <layout_type L = DL>
auto crbegin() const noexcept
  -> const_reverse_layout_iterator<L> {
  return const_reverse_layout_iterator<L>(get_cend<L>(true));
}

/**
 * Returns a constant iterator to the element following the last element
 * of the reversed expression.
 * @tparam L layout used for the traversal. Default value is \c DEFAULT_LAYOUT.
 */

template <layout_type L = DL>
auto crend() const noexcept
  -> const_reverse_layout_iterator<L> {
  return const_reverse_layout_iterator<L>(get_cbegin<L>(true));
}
//@}

/**
 * @name Constant broadcast iterators
 */
//@{
/**
 * Returns a constant iterator to the first element of the expression. The
 * iteration is broadcasted to the specified shape.
 * @param shape the shape used for broadcasting
 * @tparam S type of the \c shape parameter.
 * @tparam L layout used for the traversal. Default value is \c DEFAULT_LAYOUT.
 */

template <class S, layout_type L = DL>
auto begin(const S& shape) const noexcept
  -> const_broadcast_iterator<S, L> {
  return cbegin<S, L>(shape);
}

/**
 * Returns a constant iterator to the element following the last element of the
 * expression. The iteration is broadcasted to the specified shape.
 * @param shape the shape used for broadcasting
 * @tparam S type of the \c shape parameter.
 * @tparam L layout used for the traversal. Default value is \c DEFAULT_LAYOUT.
 */

template <class S, layout_type L = DL>
auto end(const S& shape) const noexcept
  -> const_broadcast_iterator<S, L> {
  return cend<S, L>(shape);
}

/**
 * Returns a constant iterator to the first element of the expression. The
 * iteration is broadcasted to the specified shape.
 * @param shape the shape used for broadcasting
 * @tparam S type of the \c shape parameter.
 * @tparam L layout used for the traversal. Default value is \c DEFAULT_LAYOUT.
 */

template <class S, layout_type L = DL>
auto cbegin(const S& shape) const noexcept
  -> const_broadcast_iterator<S, L> {
  return get_cbegin<S, L>(shape, false);
}

/**
 * Returns a constant iterator to the element following the last element of the
 * expression. The iteration is broadcasted to the specified shape.
 * @param shape the shape used for broadcasting
 * @tparam S type of the \c shape parameter.
 * @tparam L layout used for the traversal. Default value is \c DEFAULT_LAYOUT.
 */

template <class S, layout_type L = DL>
auto cend(const S& shape) const noexcept
  -> const_broadcast_iterator<S, L> {
  return get_cend<S, L>(shape, false);
}
//@}

/**
 * Constant reverse broadcast iterators
 */
//@{
/**
 * Returns a constant iterator to the first element of the reversed expression.
 * The iteration is broadcasted to the specified shape.
 * @param shape the shape used for broadcasting
 * @tparam S type of the \c shape parameter.
 * @tparam L layout used for the traversal. Default value is \c DEFAULT_LAYOUT.
 */

template <class S, layout_type L = DL>
auto rbegin(const S& shape) const noexcept
  -> const_reverse_broadcast_iterator<S, L> {
  return crbegin<S, L>(shape);
}

/**
 * Returns a constant iterator to the element following the last element of the
 * reversed expression. The iteration is broadcasted to the specified shape.
 * @param shape the shape used for broadcasting
 * @tparam S type of the \c shape parameter.
 * @tparam L layout used for the traversal. Default value is \c DEFAULT_LAYOUT.
 */

template <class S, layout_type L = DL>
auto rend(const S& shape) const noexcept
  -> const_reverse_broadcast_iterator<S, L> {
  return crend<S, L>(shape);
}

/**
 * Returns a constant iterator to the first element of the reversed expression.
 * The iteration is broadcasted to the specified shape.
 * @param shape the shape used for broadcasting
 * @tparam S type of the \c shape parameter.
 * @tparam L layout used for the traversal. Default value is \c DEFAULT_LAYOUT.
 */

template <class S, layout_type L = DL>
auto crbegin(const S& shape) const noexcept
  -> const_reverse_broadcast_iterator<S, L> {
  return const_reverse_broadcast_iterator<S, L>(get_cend<S, L>(shape, true));
}

/**
 * Returns a constant iterator to the element following the last element of the
 * reversed expression. The iteration is broadcasted to the specified shape.
 * @param shape the shape used for broadcasting
 * @tparam S type of the \c shape parameter.
 * @tparam L layout used for the traversal. Default value is \c DEFAULT_LAYOUT.
 */

template <class S, layout_type L = DL>
auto crend(const S& shape) const noexcept
  -> const_reverse_broadcast_iterator<S, L> {
  return const_reverse_broadcast_iterator<S, L>(get_cbegin<S, L>(shape, true));
}
//@}


template <layout_type L = DL>
auto storage_begin() const noexcept
  -> const_layout_iterator<L> {
  return cbegin<L>();
}


template <layout_type L = DL>
auto storage_end() const noexcept
  -> const_layout_iterator<L> {
  return cend<L>();
}


template <layout_type L = DL>
auto storage_cbegin() const noexcept
  -> const_layout_iterator<L> {
  return cbegin<L>();
}


template <layout_type L = DL>
auto storage_cend() const noexcept
  -> const_layout_iterator<L> {
  return cend<L>();
}


template <layout_type L = DL>
auto storage_rbegin() const noexcept
  -> const_reverse_layout_iterator<L> {
  return crbegin<L>();
}


template <layout_type L = DL>
auto storage_rend() const noexcept
  -> const_reverse_layout_iterator<L> {
  return crend<L>();
}


template <layout_type L = DL>
auto storage_crbegin() const noexcept
  -> const_reverse_layout_iterator<L> {
  return crbegin<L>();
}


template <layout_type L = DL>
auto storage_crend() const noexcept
  -> const_reverse_layout_iterator<L> {
  return crend<L>();
}


template <layout_type L = DL>
auto get_cbegin(bool reverse) const noexcept
  -> const_layout_iterator<L> {
  return const_layout_iterator<L>(get_stepper_begin(get_shape()), &get_shape(), reverse);
}


template <layout_type L = DL>
auto get_cend(bool reverse) const noexcept
  -> const_layout_iterator<L> {
  return const_layout_iterator<L>(get_stepper_end(get_shape(), L), &get_shape(), reverse);
}


template <class S, layout_type L = DL>
auto get_cbegin(const S& shape, bool reverse) const
  noexcept -> const_broadcast_iterator<S, L> {
  return const_broadcast_iterator<S, L>(get_stepper_begin(shape), shape, reverse);
}


template <class S, layout_type L = DL>
auto get_cend(const S& shape, bool reverse) const
  noexcept -> const_broadcast_iterator<S, L> {
  return const_broadcast_iterator<S, L>(get_stepper_end(shape, L), shape, reverse);
}


template <class S>
auto get_stepper_begin(const S& shape) const noexcept
  -> const_stepper {
  return derived_cast().stepper_begin(shape);
}


template <class S>
auto get_stepper_end(const S& shape, layout_type l) const noexcept
  -> const_stepper {
  return derived_cast().stepper_end(shape, l);
}


auto get_shape() const -> const inner_shape_type& {
  return derived_cast().shape();
}


auto derived_cast() const -> const derived_type& {
  return *static_cast<const derived_type*>(this);
}
};

/*************
 * xiterable *
 *************/

/**
 * @class xiterable
 * @brief Base class for multidimensional iterable expressions
 *
 * The xiterable class defines the interface for multidimensional
 * expressions that can be iterated.
 *
 * @tparam D The derived type, i.e. the inheriting class for which xiterable
 *           provides the interface.
 */
template <class D>
class xiterable : public xconst_iterable<D> {
 public:
  using derived_type = D;

  using base_type        = xconst_iterable<D>;
  using inner_shape_type = typename base_type::inner_shape_type;

  using stepper       = typename base_type::stepper;
  using const_stepper = typename base_type::const_stepper;

  template <layout_type L>
  using layout_iterator = typename base_type::template layout_iterator<L>;
  template <layout_type L>
  using const_layout_iterator =
    typename base_type::template const_layout_iterator<L>;
  template <layout_type L>
  using reverse_layout_iterator =
    typename base_type::template reverse_layout_iterator<L>;
  template <layout_type L>
  using const_reverse_layout_iterator =
    typename base_type::template const_reverse_layout_iterator<L>;

  template <class S, layout_type L>
  using broadcast_iterator =
    typename base_type::template broadcast_iterator<S, L>;
  template <class S, layout_type L>
  using const_broadcast_iterator =
    typename base_type::template const_broadcast_iterator<S, L>;
  template <class S, layout_type L>
  using reverse_broadcast_iterator =
    typename base_type::template reverse_broadcast_iterator<S, L>;
  template <class S, layout_type L>
  using const_reverse_broadcast_iterator =
    typename base_type::template const_reverse_broadcast_iterator<S, L>;

  using iterator               = typename base_type::iterator;
  using const_iterator         = typename base_type::const_iterator;
  using reverse_iterator       = typename base_type::reverse_iterator;
  using const_reverse_iterator = typename base_type::const_reverse_iterator;

  using base_type::begin;
  using base_type::end;
  using base_type::rbegin;
  using base_type::rend;
  using base_type::storage_begin;
  using base_type::storage_end;

/****************************
 * xiterable implementation *
 ****************************/

/**
 * @name Iterators
 */
//@{
/**
 * Returns an iterator to the first element of the expression.
 * @tparam L layout used for the traversal. Default value is \c DEFAULT_LAYOUT.
 */

template <layout_type L = DL>
auto begin() noexcept -> layout_iterator<L> {
  return get_begin<L>(false);
}

/**
 * Returns an iterator to the element following the last element
 * of the expression.
 * @tparam L layout used for the traversal. Default value is \c DEFAULT_LAYOUT.
 */

template <layout_type L = DL>
auto end() noexcept -> layout_iterator<L> {
  return get_end<L>(false);
}
//@}

/**
 * @name Reverse iterators
 */
//@{
/**
 * Returns an iterator to the first element of the reversed expression.
 * @tparam L layout used for the traversal. Default value is \c DEFAULT_LAYOUT.
 */

template <layout_type L = DL>
auto rbegin() noexcept -> reverse_layout_iterator<L> {
  return reverse_layout_iterator<L>(get_end<L>(true));
}

/**
 * Returns an iterator to the element following the last element
 * of the reversed expression.
 * @tparam L layout used for the traversal. Default value is \c DEFAULT_LAYOUT.
 */

template <layout_type L = DL>
auto rend() noexcept -> reverse_layout_iterator<L> {
  return reverse_layout_iterator<L>(get_begin<L>(true));
}
//@}

/**
 * @name Broadcast iterators
 */
//@{
/**
 * Returns an iterator to the first element of the expression. The
 * iteration is broadcasted to the specified shape.
 * @param shape the shape used for broadcasting
 * @tparam S type of the \c shape parameter.
 * @tparam L layout used for the traversal. Default value is \c DEFAULT_LAYOUT.
 */

template <class S, layout_type L = DL>
auto begin(const S& shape) noexcept
  -> broadcast_iterator<S, L> {
  return get_begin<S, L>(shape, false);
}

/**
 * Returns an iterator to the element following the last element of the
 * expression. The iteration is broadcasted to the specified shape.
 * @param shape the shape used for broadcasting
 * @tparam S type of the \c shape parameter.
 * @tparam L layout used for the traversal. Default value is \c DEFAULT_LAYOUT.
 */

template <class S, layout_type L = DL>
auto end(const S& shape) noexcept
  -> broadcast_iterator<S, L> {
  return get_end<S, L>(shape, false);
}
//@}

/**
 * @name Reverse broadcast iterators
 */
//@{
/**
 * Returns an iterator to the first element of the reversed expression. The
 * iteration is broadcasted to the specified shape.
 * @param shape the shape used for broadcasting
 * @tparam S type of the \c shape parameter.
 * @tparam L layout used for the traversal. Default value is \c DEFAULT_LAYOUT.
 */

template <class S, layout_type L = DL>
auto rbegin(const S& shape) noexcept
  -> reverse_broadcast_iterator<S, L> {
  return reverse_broadcast_iterator<S, L>(get_end<S, L>(shape, true));
}

/**
 * Returns an iterator to the element following the last element of the
 * reversed expression. The iteration is broadcasted to the specified shape.
 * @param shape the shape used for broadcasting
 * @tparam S type of the \c shape parameter.
 * @tparam L layout used for the traversal. Default value is \c DEFAULT_LAYOUT.
 */

template <class S, layout_type L = DL>
auto rend(const S& shape) noexcept
  -> reverse_broadcast_iterator<S, L> {
  return reverse_broadcast_iterator<S, L>(get_begin<S, L>(shape, true));
}
//@}


template <layout_type L = DL>
auto storage_begin() noexcept -> layout_iterator<L> {
  return begin<L>();
}


template <layout_type L = DL>
auto storage_end() noexcept -> layout_iterator<L> {
  return end<L>();
}


template <layout_type L = DL>
auto storage_rbegin() noexcept
  -> reverse_layout_iterator<L> {
  return rbegin<L>();
}


template <layout_type L = DL>
auto storage_rend() noexcept
  -> reverse_layout_iterator<L> {
  return rend<L>();
}


template <layout_type L = DL>
auto get_begin(bool reverse) noexcept
  -> layout_iterator<L> {
  return layout_iterator<L>(get_stepper_begin(this->get_shape()),
                            &(this->get_shape()), reverse);
}


template <layout_type L = DL>
auto get_end(bool reverse) noexcept -> layout_iterator<L> {
  return layout_iterator<L>(get_stepper_end(this->get_shape(), L),
                            &(this->get_shape()), reverse);
}


template <class S, layout_type L = DL>
auto get_begin(const S& shape, bool reverse) noexcept
  -> broadcast_iterator<S, L> {
  return broadcast_iterator<S, L>(get_stepper_begin(shape), shape, reverse);
}


template <class S, layout_type L = DL>
auto get_end(const S& shape, bool reverse) noexcept
  -> broadcast_iterator<S, L> {
  return broadcast_iterator<S, L>(get_stepper_end(shape, L), shape, reverse);
}


template <class S>
auto get_stepper_begin(const S& shape) noexcept
  -> stepper {
  return derived_cast().stepper_begin(shape);
}


template <class S>
auto get_stepper_end(const S& shape,
                                          layout_type l) noexcept -> stepper {
  return derived_cast().stepper_end(shape, l);
}


template <class S>
auto get_stepper_begin(const S& shape) const noexcept
  -> const_stepper {
  return derived_cast().stepper_begin(shape);
}


template <class S>
auto get_stepper_end(const S& shape, layout_type l) const
  noexcept -> const_stepper {
  return derived_cast().stepper_end(shape, l);
}


auto derived_cast() -> derived_type& {
  return *static_cast<derived_type*>(this);
}

};

#undef DL



}

#endif
