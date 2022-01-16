/*##########################################################################################

	Crafterra Library 🌏

	[Planning and Production]
	2017-2022 Kasugaccho
	2018-2022 As Project

	[Contact Us]
	wanotaitei@gmail.com
	https://github.com/AsPJT/Crafterra

	[License]
	Distributed under the CC0 1.0.
	https://creativecommons.org/publicdomain/zero/1.0/

##########################################################################################*/

#ifndef INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_BASIC_SIZE2D_HPP
#define INCLUDED_CRAFTERRA_LIBRARY_CRAFTERRA_BASIC_SIZE2D_HPP

namespace Crafterra {

	template<typename SizeType>
	class Size2D {
	private:

		SizeType start_x;
		SizeType start_y;
		SizeType center_x;
		SizeType center_y;
		SizeType end_x;
		SizeType end_y;

		SizeType width;
		SizeType height;
		SizeType width_half;
		SizeType height_half;

	public:
		constexpr Size2D(const SizeType width_, const SizeType height_) :
			width(width_), height(height_)
			, width_half(width_ / 2), height_half(height_ / 2)
			, start_x(0), start_y(0)
			, center_x(width_ / 2), center_y(height_ / 2)
			, end_x(width_), end_y(height_) {}

		constexpr Size2D(const SizeType start_x_, const SizeType start_y_, const SizeType width_, const SizeType height_) :
			width(width_), height(height_)
			, width_half(width_ / 2), height_half(height_ / 2)
			, start_x(start_x_), start_y(start_y_)
			, center_x(start_x_ + width_ / 2), center_y(start_y_ + height_ / 2)
			, end_x(start_x_ + width_), end_y(start_y_ + height_) {}

		constexpr SizeType getStartX() const { return this->start_x; }
		constexpr SizeType getStartY() const { return this->start_y; }
		constexpr SizeType getCenterX() const { return this->center_x; }
		constexpr SizeType getCenterY() const { return this->center_y; }
		constexpr SizeType getEndX() const { return this->end_x; }
		constexpr SizeType getEndY() const { return this->end_y; }
		constexpr SizeType getWidth() const { return this->width; }
		constexpr SizeType getHeight() const { return this->height; }
		constexpr SizeType getWidthHalf() const { return this->width_half; }
		constexpr SizeType getHeightHalf() const { return this->height_half; }

		void moveX(const SizeType move_value_) {
			this->start_x += move_value_;
			this->center_x += move_value_;
			this->end_x += move_value_;
		}

		void moveY(const SizeType move_value_) {
			this->start_y += move_value_;
			this->center_y += move_value_;
			this->end_y += move_value_;
		}
		//void setStartX(const SizeType value_) { this->start_x = value_; }
		//void setStartY(const SizeType value_) { this->start_y = value_; }
		//void setCenterX(const SizeType value_) { this->center_x = value_; }
		//void setCenterY(const SizeType value_) { this->center_y = value_; }
		//void setEndX(const SizeType value_) { this->end_x = value_; }
		//void setEndY(const SizeType value_) { this->end_y = value_; }

		void setWidth(const SizeType value_) {
			this->width = value_;
			this->width_half = value_ / 2;
			this->start_x = (this->center_x - this->width_half);
			this->end_x = (this->center_x + this->width_half);
		}
		void setHeight(const SizeType value_) {
			this->height = value_;
			this->height_half = value_ / 2;
			this->start_y = (this->center_y - this->height_half);
			this->end_y = (this->center_y + this->height_half);
		}
		void setSize(const SizeType value_) {
			this->setWidth(value_);
			this->setHeight(value_);
		}
		void setWidthHalf(const SizeType value_) { this->setWidth(value_ * 2); }
		void setHeightHalf(const SizeType value_) { this->setHeight(value_ * 2); }
	};

}

#endif //Included Crafterra Library